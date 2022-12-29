#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_IMAGE_BITMAP_RENDERING_CONTEXT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_IMAGE_BITMAP_RENDERING_CONTEXT_HPP


namespace html::canvasing {class image_bitmap_rendering_context;}

#include INCLUDE_INNER_TYPES(html)
namespace html::canvasing {class image_bitmap;}
namespace html::canvasing {class offscreen_canvas;}
namespace html::elements {class html_canvas_element;}


class html::canvasing::image_bitmap_rendering_context
        : public virtual dom_object
{
public constructors:
    image_bitmap_rendering_context() = default;
    ~image_bitmap_rendering_context();

public js_methods:
    auto transfer_from_image_bitmap(image_bitmap* bitmap) -> void;

private js_properties:
    ext::property<elements::html_canvas_element*, offscreen_canvas*> canvas;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    detail::bitmap_mode_t bitmap_mode;
    ext::boolean alpha;
    std::unique_ptr<detail::image_bitmap_t> m_output_bitmap;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_IMAGE_BITMAP_RENDERING_CONTEXT_HPP
