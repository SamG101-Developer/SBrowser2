#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_CANVAS_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_CANVAS_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_canvas_element;}

#include "ext/any.hpp"
#include USE_INNER_TYPES(html)
namespace html::canvasing {class offscreen_canvas;}
namespace mediacapture::main {class media_stream;}


class html::elements::html_canvas_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_canvas_element);
    html_canvas_element() = default;

public js_methods:
    /* HTML */
    auto get_context(ext::string_view context_id, ext::any&& options = nullptr) -> detail::rendering_context_t;
    auto to_data_url(ext::string_view type = "image/png", ext::any&& quality = nullptr) -> ext::string;
    auto to_blob(detail::blob_callback_t&& callback, ext::string_view type = "image/png", ext::any&& quality = nullptr) -> file_api::blob;
    auto transfer_control_to_offscreen() -> canvasing::offscreen_canvas;

    /* MEDIACAPTURE-FROMELEMENT */
    auto capture_stream(const ext::number<double>& frame_request_rate) -> mediacapture::main::media_stream;

public js_properties:
    ext::property<ext::number<ulong>> width;
    ext::property<ext::number<ulong>> height;

private cpp_methods:
    detail::canvas_context_mode_t m_canvas_context_mode;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_CANVAS_ELEMENT_HPP
