#include "html_iframe_element.hpp"

#include "html/detail/context_internals.hpp"
#include "html/detail/html_element_internals.hpp"


html::elements::html_iframe_element::html_iframe_element()
{
    m_dom_behaviour.insertion_steps = [this]
    {
        detail::context_internals::create_new_nested_browsing_context(this);
        detail::html_element_internals::process_iframe_attributes(this, ext::boolean::TRUE());
    };
    HTML_CONSTRUCTOR
}
