#include "algorithm_internals.hpp"

#include "ext/span.hpp"





#include "html/detail/context_internals.hpp"
#include "html/elements/html_iframe_element.hpp"

#include "fetch/detail/header_internals.hpp"
#include "fetch/detail/request_internals.hpp"
#include "fetch/detail/response_internals.hpp"

#include "content_security_policy/detail/csp_internals.hpp"
#include "permissions_policy/detail/policy_internals.hpp"
#include "permissions_policy/permissions_policy_violation_report_body.hpp"

#include <magic_enum.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/map.hpp>


auto permissions_policy::detail::algorithm_internals::is_valid_feature(
        const feature_name_t& feature_name)
        -> ext::boolean
{
    // a feature name is valid if it maps to a feature in the 'feature_t' enum class. use a 'enum_contains' check from
    // the magic_enum library to determine this
    return magic_enum::enum_contains<feature_t>(feature_name);
}


auto permissions_policy::detail::algorithm_internals::process_response_body(
        const fetch::detail::response_t& response,
        ext::string&& origin)
        -> declared_policy_t
{
    using enum fetch::detail::header_value_object_t;
    
    auto parsed_header = fetch::detail::get_structured_field_value<DICT>("Permissions-Policy", response.header_list);
    auto policy = construct_policy_from_dictionary_and_origin(parsed_header, std::move(origin));
    return policy;
}


auto permissions_policy::detail::algorithm_internals::construct_policy_from_dictionary_and_origin(
        ext::map_view<feature_name_t, ext::vector<ext::string>> dictionary,
        ext::string&& origin)
        -> declared_policy_t
{
    declared_policy_t policy;

    // iterate over each feature name and value in the dictionary - this is a map that says for each feature, which urls
    // are allowed, with some eXtra customization options such as the "self" and "*" tokens
    for (const auto& [feature_name, value]: dictionary)
    {
        continue_if(!is_valid_feature(feature_name));
        auto feature = magic_enum::enum_cast<feature_t>(feature_name).value();

        // create the 'allowlist', which is a set or url origins that are allowed to use the feature. if the value is
        // the special "*" token, then set the 'allowlist' to "*", to indicate that any origin can use thus feature
        allowlist_t allowlist;
        if (ranges::contains(value, "*"))
            allowlist = {"*"};

        // otherwise, iterate over each item in the value, parse the value, and (possible) insert the parsed value into
        // the 'allowlist' set
        else
        {
            for (const auto& element: value)
            {
                // special case for the "self" token is to insert the origin into the 'allowlist' - this means that the
                // origin provided is allowed to use teh feature
                if (element == "self")
                {
                    allowlist.insert(std::move(origin));
                    continue;
                }

                // parse the item that it being inspected (a string-type url), and if the parsing hasn't failed, and the
                // origin of the url is opaque, then insert the origin into the allowlist. this means that this specific
                // origin can use the feature
                auto url_record = url::detail::url_internals::url_parser(element);
                if (url_record && !url::detail::url_internals::is_opaque_origin(url_record->origin))
                    allowlist.insert(url_record->origin);
            }
        }

        // insert the 'feature_name'-'allowlist' into the policy
        policy.insert_or_assign(feature, allowlist);
    }

    return policy;
}


auto permissions_policy::detail::algorithm_internals::parse_policy_directive(
        ext::string&& value,
        ext::string&& origin,
        ext::string&& target_origin)
        -> policy_directive_t
{
    policy_directive_t directive;

    for (auto&& serialized_declaration: value | ranges::views::split_string(';'))
    {
        auto tokens = serialized_declaration | ranges::views::split_string(' ');
        continue_if(tokens.empty());

        auto feature_name = tokens.front();
        continue_if(!is_valid_feature(feature_name));

        auto feature = magic_enum::enum_cast<feature_t>(feature_name).value();
        auto target_list = ext::vector_view<ext::string>(ranges::next(tokens.begin()), tokens.end());
        allowlist_t allowlist;

        if (ranges::contains(target_list, "*"))
            allowlist = {"*"};

        else
        {
            if (target_list.empty() && !target_origin.empty())
                allowlist.insert(target_origin);

            for (const auto& element: target_list)
            {
                if (element == "self")
                    allowlist.insert(target_origin);

                auto url_record = element == "src" && !target_origin.empty()
                        ? target_origin
                        : url::detail::url_internals::url_parser(element);

                if (url_record && !url::detail::url_internals::is_opaque_origin(url_record->origin))
                    allowlist.insert(url_record->origin);
            }
        }

        directive.insert_or_assign(feature, allowlist);
    }

    return directive;
}


auto permissions_policy::detail::algorithm_internals::process_permissions_policy_attributes(
        const allowable_element auto* element)
        -> container_policy_t
{
    auto container_policy = parse_policy_directive(element->allow(), element->owner_document()->m_origin, policy_internals::declared_origin(element));
    if (element->local_name() == "iframe" && dynamic_cast<html::elements::html_iframe_element*>(element)->allow_fullscreen())
        container_policy.emplace(feature_t::FULLSCREEN, {"*"});

    return container_policy;

}


auto permissions_policy::detail::algorithm_internals::create_permissions_policy_for_browsing_context(
        html::detail::browsing_context& context,
        ext::string&& origin)
        -> internal_permissions_policy_t
{
    auto policy_definition_method = [origin = std::move(origin), &context](feature_t feature) mutable
    {
        return ext::make_pair(feature, define_inherited_policy_for_feature_in_browsing_context(feature, std::move(origin), context));
    };

    auto inherited_policy = magic_enum::enum_entries<feature_t>() | ranges::views::keys
            | ranges::views::transform(policy_definition_method)
            | ranges::to<inherited_policy_t>;

    internal_permissions_policy_t policy {.inherited_policy = inherited_policy};
    return policy;
}


auto permissions_policy::detail::algorithm_internals::create_permissions_policy_for_feature_in_container_at_origin(
        const allowable_element auto* allowable_element,
        ext::string&& origin)
        -> internal_permissions_policy_t
{
    auto policy_definition_method = [origin = std::move(origin), allowable_element](feature_t feature) mutable
    {
        return ext::make_pair(feature, define_inherited_policy_for_feature_in_container_at_origin(feature, allowable_element, std::move(origin)));
    };

    auto inherited_policy = magic_enum::enum_entries<feature_t>() | ranges::views::keys
            | ranges::views::transform(policy_definition_method)
            | ranges::to<inherited_policy_t>;
    
    internal_permissions_policy_t policy {.inherited_policy = inherited_policy};
    return policy;
}


auto permissions_policy::detail::algorithm_internals::create_permissions_policy_for_browsing_context_from_response(
        html::detail::browsing_context& context,
        ext::string&& origin,
        fetch::detail::response_t& response)
        -> internal_permissions_policy_t
{
    using enum inherited_policy_value_t;
    auto policy = create_permissions_policy_for_browsing_context(context, std::move(origin));
    auto declared_policy = process_response_body(response, std::move(origin));

    policy.declared_policy = declared_policy
            | ranges::views::filter([&policy](auto&& pair) {return policy.inherited_policy.at(pair.first) == ENABLED;})
            | ranges::to<declared_policy_t>;

    return policy;
}


auto permissions_policy::detail::algorithm_internals::define_inherited_policy_for_feature_in_browsing_context(
        feature_t feature,
        ext::string&& origin,
        html::detail::browsing_context& context)
        -> inherited_policy_value_t
{
    using enum inherited_policy_value_t;
    // TODO : ?
    return ENABLED;
}


auto permissions_policy::detail::algorithm_internals::define_inherited_policy_for_feature_in_container_at_origin(
        feature_t feature,
        const allowable_element auto* context_container,
        ext::string&& origin)
        -> inherited_policy_value_t
{
    using enum inherited_policy_value_t;

    auto& policy = *context_container->owner_document()->m_permissions_policy;
    return_if(policy.inherited_policy.at(feature) == DISABLED) DISABLED;
    return_if(policy.declared_policy.contains(feature) && policy.declared_policy.at(feature) != allowlist_t{std::move(origin)}) DISABLED;

    auto container_policy = process_permissions_policy_attributes(context_container);
    return_if(container_policy.contains(feature)) magic_enum::enum_value<inherited_policy_value_t>(allow_list_origin_matches(container_policy.at(feature), allowlist_t{std::move(origin)}));

    return_if(default_allowlist(feature) == allowlist_t{"*"}) ENABLED;
    return_if(default_allowlist(feature) == allowlist_t{"self"} && html::detail::same_origin(origin, context_container->owner_document()->m_origin)) ENABLED;
    return DISABLED;
}


auto permissions_policy::detail::algorithm_internals::is_feature_enabled_in_document_for_origin(
        feature_t feature,
        dom::nodes::document* document,
        ext::string&& origin)
        -> inherited_policy_value_t
{
    using enum inherited_policy_value_t;

    auto& policy = *document->m_permissions_policy;
    return_if(policy.inherited_policy.at(feature) == DISABLED) DISABLED;
    return_if(policy.declared_policy.contains(feature)) magic_enum::enum_value<inherited_policy_value_t>(allow_list_origin_matches(policy.declared_policy.at(feature), allowlist_t{std::move(origin)}));
    return_if(default_allowlist(feature) == allowlist_t{"*"}) ENABLED;
    return_if(default_allowlist(feature) == allowlist_t{"self"} && html::detail::same_origin(origin, document->m_origin)) ENABLED;
    return DISABLED;
}


auto permissions_policy::detail::algorithm_internals::generate_report_for_violation_of_permissions_policy_on_settings(
        feature_t feature,
        v8::Local<v8::Object> settings,
        ext::string&& group)
        -> void
{
    using disposition_t = content_security_policy::detail::disposition_t;

    permissions_policy::permissions_policy_violation_report_body body;
    body.feature_id = ext::string{magic_enum::enum_name(feature)};
    body.disposition = ext::string{magic_enum::enum_name(disposition_t::ENFORCE)};

    // TODO : other attributes
    group = group.empty() ? "default" : group;
    reporting::detail::queue_report(body, "permissions-policy-violation", group, settings);
}


auto permissions_policy::detail::algorithm_internals::should_request_be_allowed_to_use_feature(
        feature_t feature,
        fetch::detail::request_t& request)
        -> ext::boolean
{
    using enum inherited_policy_value_t;

    auto* window = v8pp::from_v8<dom::nodes::window*>(request.window->GetIsolate(), request.window);
    return_if(!window) false;

    auto* document = window->document();
    return is_feature_enabled_in_document_for_origin(feature, document, std::move(request.origin)) == ENABLED;
}
