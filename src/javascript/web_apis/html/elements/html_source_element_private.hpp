#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SOURCE_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SOURCE_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"


DEFINE_PRIVATE_CLASS(html::elements, html_source_element) : html::elements::html_element_private
{
    ext::string src;
    ext::string type;
    ext::string srcset;
    ext::string sizes;
    ext::string media;
    ext::number<ulong> width;
    ext::number<ulong> height;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SOURCE_ELEMENT_PRIVATE_HPP
