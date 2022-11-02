#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_STYLE_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_STYLE_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"
#include "css/cssom/mixins/link_style_private.hpp"


DEFINE_PRIVATE_CLASS(html::elements, html_style_element)
        : html::elements::html_element_private
        , css::cssom::mixins::link_style_private
{
    ext::string media;
    ext::vector<detail::blocking_t> blocking;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_STYLE_ELEMENT_PRIVATE_HPP
