#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"

#include "ext/ranges.hpp"


DEFINE_PRIVATE_CLASS(html::elements, html_table_element) : html::elements::html_element_private
{
    template <typename T>
    auto table_children(ext::string&& local_name = u8"*") const -> ranges::any_helpful_view<T*>;

    template <typename ...Types>
    auto table_children(ext::string&& local_name = u8"*") const -> ranges::any_helpful_view<html_element*> requires (sizeof...(Types) > 1);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_PRIVATE_HPP
