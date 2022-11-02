#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SELECT_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SELECT_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"

#include <range/v3/view/join.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/concat.hpp>
namespace html::elements {class html_form_element;}
namespace html::elements {class html_option_element;}
namespace html::elements {class html_opt_group_element;}
namespace html::elements {class html_opt_group_element_private;}


DEFINE_PRIVATE_CLASS(html::elements, html_select_element) : html::elements::html_element_private
{
    ext::string autocomplete;
    ext::boolean disabled;
    std::observer_ptr<html_form_element> form_owner;

    ext::boolean multiple;
    ext::string name;
    ext::boolean required;
    ext::number<ulong> size;

    _EXT_NODISCARD auto list_of_options() const
    {
        decltype(auto) option_children = child_nodes | ranges::views::cast<elements::html_option_element*>;
        decltype(auto) option_grandchildren = child_nodes
                | ranges::views::cast<elements::html_opt_group_element*>
                | ranges::views::transform(&html_opt_group_element_private::child_nodes, ext::get_pimpl)
                | ranges::views::transform(&std::unique_ptr<dom::nodes::node>::get)
                | ranges::views::join
                | ranges::views::cast<elements::html_option_element*>;
        return ranges::views::concat(option_children, option_grandchildren);
    }
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SELECT_ELEMENT_PRIVATE_HPP
