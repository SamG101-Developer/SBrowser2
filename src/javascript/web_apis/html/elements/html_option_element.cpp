#include "html_option_element.hpp"

#include "ext/casting.hpp"

#include "html/detail/form_controlled_internals.hpp"
#include "html/elements/html_select_element.hpp"


html::elements::html_option_element::html_option_element()
{
    m_dom_behaviour.insertion_steps =
            [this]
            {
                if (decltype(auto) parent = dom_cast<html_select_element*>(parent_node()))
                    detail::selectedness_settings_algorithm(parent);

                else if (decltype(auto) grandparent = dom_cast<html_select_element*>(parent_node()->parent_node()); dom_cast<html_opt_group_element*>(parent_node()) && grandparent)
                    detail::selectedness_settings_algorithm(grandparent);
            };

    m_dom_behaviour.remove_steps =
            [this](dom::nodes::node* old_parent)
            {
                if (decltype(auto) parent = dom_cast<html_select_element*>(parent_node()))
                    detail::selectedness_settings_algorithm(parent);

                else if (decltype(auto) grandparent = dom_cast<html_select_element*>(parent_node()->parent_node()); dom_cast<html_opt_group_element*>(parent_node()) && grandparent)
                    detail::selectedness_settings_algorithm(grandparent);
            };
}
