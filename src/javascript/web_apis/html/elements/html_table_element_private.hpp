#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"


DEFINE_PRIVATE_CLASS(html::elements, html_table_element) : html::elements::html_element_private
{
    template <typename T>
    auto table_children() const -> ext::vector_span<T*>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TABLE_ELEMENT_PRIVATE_HPP
