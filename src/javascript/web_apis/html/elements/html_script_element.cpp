#include "html_script_element.hpp"

#include "ext/casting.hpp"


html::elements::html_script_element::html_script_element()
{
    m_dom_behaviour.cloning_steps =
            [this](dom::nodes::node* clone, dom::nodes::document* document_to_clone_into, ext::boolean&& deep)
            {
                dom_cast<html_script_element*>(clone)->m_already_started = m_already_started;
            };

    HTML_CONSTRUCTOR;
}
