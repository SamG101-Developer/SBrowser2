#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_CANVAS_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_CANVAS_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "html/elements/html_element_private.hpp"

#include INCLUDE_INNER_TYPES(html)
namespace html::canvasing {class image_bitmap;}


DEFINE_PRIVATE_CLASS(html::elements, html_canvas_element) : html::elements::html_element_private
{
    detail::canvas_context_mode_t canvas_context_mode;
    detail::rendering_context_t context;
    std::unique_ptr<canvasing::image_bitmap> bitmap;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_CANVAS_ELEMENT_PRIVATE_HPP
