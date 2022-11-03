#include "custom_element_registry.hpp"
#include "custom_element_registry_private.hpp"

#include "dom/detail/shadow_internals.hpp"
#include "ext/functional.hpp"
#include "ext/ranges.hpp"

#include "javascript/interop/manual_primitive_conversions/convert_string.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/namespace_internals.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/element_private.hpp"
#include "dom/nodes/node.hpp"
#include "dom/nodes/node_private.hpp"
#include "dom/nodes/window.hpp"


auto html::other::custom_element_registry::define(
        ext::string_view name,
        detail::custom_element_constructor_t&& constructor,
        detail::element_definition_options_t&& options)
        -> void
{
    ACCESS_PIMPL(custom_element_registry);
    JS_REALM_GET_RELEVANT(this);
    using enum v8_primitive_error_t;
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [this_relevant_agent, &constructor] {return !v8pp::to_v8(this_relevant_agent, constructor)->IsConstructor();},
            u8"Must be a valid constructor");

    dom::detail::throw_v8_exception<SYNTAX_ERR>(
            [name] {return !dom::detail::is_valid_custom_element_name(name);},
            u8"Must be a valid custom element name");

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d, name] {return ranges::contains(d->custom_element_definitions | ranges::views::transform_to_attr(&dom::detail::custom_element_definition_t::name, ext::deref), name);},
            u8"Name already exists");

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d, constructor] {return ranges::contains(d->custom_element_definitions | ranges::views::transform_to_attr(&dom::detail::custom_element_definition_t::constructor, ext::deref), constructor);},
            u8"Constructor already exists");

    decltype(auto) local_name = name;
    decltype(auto) extends = options[u8"extends"].to<ext::string>();
    if (!extends.empty())
    {
        dom::detail::throw_v8_exception<SYNTAX_ERR>(
                [name] {return dom::detail::is_valid_custom_element_name(name);},
                u8"Cannot extend from a valid custom element name");

        // TODO : element_interface() check
        local_name = std::move(extends);
    }

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d] {return d->element_definition_is_running;},
            u8"Cannot define a name/constructor whilst another name/constructor is being defined");

    d->element_definition_is_running = true;
    auto form_associated = ext::boolean::FALSE_();
    auto disable_internals = ext::boolean::FALSE_();
    auto disable_shadow = ext::boolean::FALSE_();
    auto observed_attributes = ext::vector<ext::string>();

    JS_EXCEPTION_HANDLER;
    using namespace ext::literals;
    decltype(auto) v8_constructor = v8pp::to_v8(this_relevant_agent, constructor);
    decltype(auto) v8_prototype = v8_constructor->GetPrototype();

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [v8_prototype] {return !v8_prototype->IsObject();},
            u8"Must be a valid constructor");

    auto lifecycle_callbacks = ext::map<ext::string, dom::detail::lifecycle_callback_t>{};

    for (auto callback_name: {u8"connectedCallback", u8"disconnectedCallback", u8"adoptedCallback", u8"attributeChangedCallback"})
    {
        auto callback_value = v8_prototype.As<v8::Object>()->Get(this_relevant_realm, v8pp::to_v8(this_relevant_agent, callback_name)).ToLocalChecked();
        auto callback = v8pp::from_v8<dom::detail::lifecycle_callback_t>(this_relevant_agent, callback_value);
        lifecycle_callbacks.try_emplace(callback_name, std::move(callback));
        JS_EXCEPTION_RETHROW_IF_HAS_THROWN;
    }

    if (!lifecycle_callbacks[u8"attributeChangedCallback"].empty())
    {
        auto observed_attributes_iterable = v8_constructor->Get(this_relevant_realm, v8pp::to_v8(this_relevant_agent, u8"observedAttributes"_es)).ToLocalChecked();
        observed_attributes = v8pp::from_v8<ext::vector<ext::string>>(this_relevant_agent, observed_attributes_iterable);
        JS_EXCEPTION_RETHROW_IF_HAS_THROWN;
    }

    auto disabled_features_iterable = v8_constructor->Get(this_relevant_realm, v8pp::to_v8(this_relevant_agent, u8"disabledFeatures"_es)).ToLocalChecked();
    auto disabled_features = v8pp::from_v8<ext::vector<ext::string>>(this_relevant_agent, disabled_features_iterable);
    JS_EXCEPTION_RETHROW_IF_HAS_THROWN;

    disable_internals = ranges::contains(disabled_features, u8"internals");
    disable_shadow = ranges::contains(disabled_features, u8"shadow");
    JS_EXCEPTION_RETHROW_IF_HAS_THROWN;

    auto form_associated_value = v8_constructor->Get(this_relevant_realm, v8pp::to_v8(this_relevant_agent, u8"formAssociated"_es)).ToLocalChecked();
    form_associated = v8pp::from_v8<ext::boolean>(this_relevant_agent, form_associated_value);
    JS_EXCEPTION_RETHROW_IF_HAS_THROWN;

    for (auto callback_name: {u8"formAssociatedCallback", u8"formResetCallback", u8"formDisabledCallback", u8"formStateRestoreCallback"})
    {
        auto callback_value = v8_prototype.As<v8::Object>()->Get(this_relevant_realm, v8pp::to_v8(this_relevant_agent, callback_name)).ToLocalChecked();
        auto callback = v8pp::from_v8<dom::detail::lifecycle_callback_t>(this_relevant_agent, callback_value);
        lifecycle_callbacks.try_emplace(callback_name, std::move(callback));
        JS_EXCEPTION_RETHROW_IF_HAS_THROWN;
    }

    // TODO : exception.Finally()
    d->element_definition_is_running = false;
    JS_EXCEPTION_RETHROW_IF_HAS_THROWN;

    decltype(auto) definition = std::make_unique<dom::detail::custom_element_definition_t>(
            name, local_name,
            std::move(constructor), std::move(observed_attributes), std::move(lifecycle_callbacks),
            form_associated, disabled_features, disable_shadow);

    d->custom_element_definitions.emplace(definition);

    decltype(auto) document = v8pp::from_v8<dom::nodes::window*>(this_relevant_agent, this_relevant_global_object)->d_func()->document;
    dom::detail::shadow_including_descendants(document)
            | ranges::views::cast<dom::nodes::element*>
            | ranges::views::filter_eq(&dom::nodes::element_private::namespace_, dom::detail::HTML, ext::get_pimpl)
            | ranges::views::filter_eq(&dom::nodes::element_private::local_name, local_name, ext::get_pimpl)
            | ranges::views::filter([extends](dom::nodes::element* child) {return extends.empty() || child->d_func()->is == extends;})
            | ranges::views::for_each(BIND_BACK(&dom::detail::enqueue_custom_element_upgrade_reaction, definition));

    if (d->when_defined_promise_map.contains(name))
    {
        d->when_defined_promise_map[name].resolve(std::move(constructor));
        d->when_defined_promise_map |= ranges::actions::remove(name);
    }
}


auto html::other::custom_element_registry::get(
        ext::string_view name)
        -> ext::optional<detail::custom_element_constructor_t>
{
    ACCESS_PIMPL(const custom_element_registry);
    return d->when_defined_promise_map.contains(name)
            ? d->when_defined_promise_map[name]
            : ext::nullopt;
}


auto html::other::custom_element_registry::when_defined(
        ext::string_view name)
        -> ext::promise<detail::custom_element_constructor_t>
{
    ACCESS_PIMPL(custom_element_registry);
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_SYNTAX_ERROR>(
            [name] {return !dom::detail::is_valid_custom_element_name(name);},
            u8"Must be a valid custom element name");

    return d->when_defined_promise_map.try_emplace(name, ext::promise<detail::custom_element_constructor_t>{}).first->second;
}


auto html::other::custom_element_registry::upgrade(dom::nodes::node* root) -> void
{
    dom::detail::shadow_including_descendants(root)
            | ranges::views::for_each(&dom::detail::try_to_upgrade_element);
}
