#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_CANVAS_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_CANVAS_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_canvas_element;}
namespace html::elements {class html_canvas_element_private;}

#include "ext/any.hpp"
#include INCLUDE_INNER_TYPES(html)
namespace html::canvasing {class offscreen_canvas;}
namespace mediacapture::main {class media_stream;}


class html::elements::html_canvas_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_canvas_element);
    MAKE_PIMPL(html_canvas_element);
    MAKE_V8_AVAILABLE;

public js_methods:
    /* [HTML] */
    auto get_context(detail::canvas_context_mode_t context_id, ext::map<ext::string, ext::any>&& options = {}) -> detail::rendering_context_t;
    auto to_data_url(ext::string_view type = "image/png", ext::any&& quality = {}) -> ext::string;
    auto to_blob(detail::blob_callback_t&& callback, ext::string_view type = "image/png", ext::any&& quality = {}) -> file_api::blob;
    auto transfer_control_to_offscreen() -> canvasing::offscreen_canvas;

    /* [MEDIACAPTURE-FROMELEMENT] */
    auto capture_stream(ext::number<double> frame_request_rate) -> mediacapture::main::media_stream;

private js_properties:
    DEFINE_GETTER(widgth, ext::number<ulong>);
    DEFINE_GETTER(height, ext::number<ulong>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_CANVAS_ELEMENT_HPP
