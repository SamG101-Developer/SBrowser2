#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_CANVAS_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_CANVAS_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_canvas_element;}

namespace mediacapture::main {class media_stream;}


class html::elements::html_canvas_element
        : public html_element
{
public js_methods:
    /* MEDIACAPTURE-FROMELEMENT */
    auto capture_stream(const ext::number<double>& frame_request_rate) -> mediacapture::main::media_stream;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_CANVAS_ELEMENT_HPP
