#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_OFFSCREEN_CANVAS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_OFFSCREEN_CANVAS_HPP

#include "dom/nodes/event_target.hpp"
#include "html/mixins/transferable.hpp"
namespace html::canvasing {class offscreen_canvas;}

#include "ext/promise.hpp"
#include INCLUDE_INNER_TYPES(html)


class html::canvasing::offscreen_canvas
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(offscreen_canvas);
    offscreen_canvas() = default;
    offscreen_canvas(ext::number<ulonglong> width, ext::number<ulonglong> height);

public js_methods:
    auto get_context(detail::offscreen_rendering_context_id_t context_id, ext::any&& options = nullptr) -> detail::offscreen_rendering_context_t;
    auto transfer_to_image_bitmap() -> image_bitmap;
    auto convert_to_block(detail::image_encode_options_t&& options = {}) -> ext::promise<file_api::blob>;

public js_properties:
    ext::property<ext::number<ulonglong>> width;
    ext::property<ext::number<ulonglong>> height;

private cpp_properties:
    std::weak_ptr<elements::html_canvas_element> m_placeholder_canvas_element;
    std::unique_ptr<detail::image_bitmap_t> m_bitmap;
    detail::canvas_context_mode_t m_mode;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_OFFSCREEN_CANVAS_HPP
