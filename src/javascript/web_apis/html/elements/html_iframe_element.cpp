#include "html_iframe_element.hpp"

#include "ext/ranges.hpp"

#include "html/detail/context_internals.hpp"
#include "html/detail/html_element_internals.hpp"
#include "html/detail/lazy_loading_internals.hpp"

#include "permissions_policy/permissions_policy.hpp"
#include "referrer_policy/_typedefs.hpp"

#include <magic_enum.hpp>


html::elements::html_iframe_element::html_iframe_element()
        : permissions_policy{std::make_unique<permissions_policy::permissions_policy_object>()}
{
    bind_get(content_document);
    bind_get(content_window);
    bind_set(sandbox);
    bind_set(loading);

    m_dom_behaviour.insertion_steps = [this]
    {
        detail::create_new_nested_browsing_context(this);
        detail::process_iframe_attributes(this, true);
    };

    permissions_policy()->m_associated_node = this;

    HTML_CONSTRUCTOR
}


auto html::elements::html_iframe_element::set_sandbox(
        ext::string_view val)
        -> void
{
    // these are the allowed values for the 'sandbox' attribute; the usual `attach_constraints` can't be used, because
    // the attribute is allowed to be multiple values (from below), so the check is done in the setter method instead
    auto allowed = {
            "allow-downloads", "allow-forms", "allow-modals", "allow-orientation-lock", "allow-pointer-lock",
            "allow-popups", "allow-popups-to-escape-sandbox", "allow-presentation", "allow-same-origin",
            "allow-scripts", "allow-top-navigation", "allow-top-navigation-by-user-activation",
            "allow-top-navigation-to-custom-protocols"};

    // split the 'val' by spaces, and filter out the value's that aren't in the 'allowed' list, join the filtered values
    // back with spaces, and convert the range back into a string
    auto filtered_sandbox_attributes = val
            | ranges::views::split_string(' ')
            | ranges::views::filter([allowed = std::move(allowed)](ext::string&& attribute) {return ranges::contains(allowed, attribute);})
            | ranges::views::join(' ')
            | ranges::to<ext::string>;

    // set the internal value of the sandbox property
    property_guard(sandbox);
    *sandbox = filtered_sandbox_attributes;
}


auto html::elements::html_iframe_element::set_loading(
        detail::lazy_loading_t val)
        -> void
{
    using detail::lazy_loading_t;

    // there is a special case for the "Eager" case where there are lazy load resumption steps: run the steps and then
    // reset them to an empty method that doesn't do anything (like a one-shot function)
    if (val == lazy_loading_t::EAGER && !m_lazy_load_resumption_steps.empty())
    {
        m_lazy_load_resumption_steps();
        m_lazy_load_resumption_steps = [] {};
    }

    // set the internal value of the sandbox property
    property_guard(loading);
    *loading = val;
}
