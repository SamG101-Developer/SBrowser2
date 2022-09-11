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
    auto get_context(detail::canvas_context_mode_t context_id, ext::map<ext::string, ext::any>&& options = {}) -> detail::rendering_context_t;
    auto to_data_url(ext::string_view type = "image/png", ext::any&& quality = {}) -> ext::string;
    auto to_blob(detail::blob_callback_t&& callback, ext::string_view type = "image/png", ext::any&& quality = {}) -> file_api::blob;
    auto transfer_control_to_offscreen() -> canvasing::offscreen_canvas;

    /* MEDIACAPTURE-FROMELEMENT */
    auto capture_stream(ext::number<double> frame_request_rate) -> mediacapture::main::media_stream;

public js_properties:
    ext::property<ext::number<ulong>> width;
    ext::property<ext::number<ulong>> height;

private cpp_properties:
    detail::canvas_context_mode_t m_canvas_context_mode;
    detail::rendering_context_t m_context;
    std::unique_ptr<canvasing::image_bitmap> m_bitmap;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_CANVAS_ELEMENT_HPP
