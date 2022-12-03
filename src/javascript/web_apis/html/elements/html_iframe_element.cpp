#include "html_iframe_element.hpp"
#include "html_iframe_element_private.hpp"



#include "html/detail/context_internals.hpp"
#include "html/detail/html_element_internals.hpp"
#include "html/detail/lazy_loading_internals.hpp"

#include "permissions_policy/permissions_policy.hpp"
#include "permissions_policy/permissions_policy_private.hpp"

#include "url/detail/url_internals.hpp"

#include <magic_enum.hpp>


html::elements::html_iframe_element::html_iframe_element()
{
    INIT_PIMPL(html_iframe_element);
    ACCESS_PIMPL(html_iframe_element);

    d->insertion_steps = [this]
    {
        detail::create_new_nested_browsing_context(this);
        detail::process_iframe_attributes(this, true);
    };

    d->permissions_policy->d_func()->associated_node = this;

    HTML_CONSTRUCTOR
}


auto html::elements::html_iframe_element::set_sandbox(
        const ext::string& val)
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
            | ranges::views::filter([allowed](ext::string&& attribute) {return ranges::contains(allowed, attribute);})
            | ranges::views::join(' ')
            | ranges::to<ext::string>;

    // set the internal value of the sandbox property
    d->sandbox = filtered_sandbox_attributes;
}


auto html::elements::html_iframe_element::set_loading(detail::lazy_loading_t new_loading) -> detail::lazy_loading_t
{
    ACCESS_PIMPL(html_iframe_element);
    using detail::lazy_loading_t;

    // there is a special case for the "Eager" case where there are lazy load resumption steps: run the steps and then
    // reset them to an empty method that doesn't do anything (like a one-shot function)
    if (new_loading == lazy_loading_t::EAGER && !d->lazy_load_resumption_steps.empty())
    {
        d->lazy_load_resumption_steps();
        d->lazy_load_resumption_steps = [] {};
    }

    // set the internal value of the sandbox property
    d->loading = new_loading;
}
