#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_IMAGE_BITMAP_RENDERING_CONTEXT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_IMAGE_BITMAP_RENDERING_CONTEXT_HPP

#include "dom_object.hpp"
namespace html::canvasing {class image_bitmap_rendering_context;}

#include USE_INNER_TYPES(html)
namespace html::canvasing {class image_bitmap;}
namespace html::canvasing {class offscreen_canvas;}
namespace html::elements {class html_canvas_element;}


class html::canvasing::image_bitmap_rendering_context
        : public virtual dom_object
{
public constructors:
    image_bitmap_rendering_context() = default;

public js_methods:
    auto transfer_from_image_bitmap(image_bitmap* bitmap) -> void;

public js_properties:
    ext::property<elements::html_canvas_element*, offscreen_canvas*> canvas;

private cpp_properties:
    detail::bitmap_mode_t bitmap_mode;
    ext::boolean alpha;
    std::unique_ptr<detail::image_bitmap_t> m_output_bitmap;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_IMAGE_BITMAP_RENDERING_CONTEXT_HPP
