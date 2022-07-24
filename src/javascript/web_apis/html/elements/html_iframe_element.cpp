#include "html_iframe_element.hpp"

#include "html/detail/context_internals.hpp"
#include "html/detail/html_element_internals.hpp"

#include "permissions_policy/permissions_policy.hpp"


html::elements::html_iframe_element::html_iframe_element()
        : permissions_policy{std::make_unique<permissions_policy::permissions_policy_object>()}
{
    m_dom_behaviour.insertion_steps = [this]
    {
        detail::context_internals::create_new_nested_browsing_context(this);
        detail::html_element_internals::process_iframe_attributes(this, ext::boolean::TRUE());
    };

    permissions_policy()->m_associated_node = this;

    HTML_CONSTRUCTOR
}
