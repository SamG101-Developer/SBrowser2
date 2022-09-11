#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_DRAW_IMAGE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_DRAW_IMAGE_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_draw_image;}

#include USE_INNER_TYPES(html)


class html::canvasing::mixins::canvas_draw_image
        : public virtual dom_object
{
public js_methods:
    auto draw_image(
            detail::canvas_image_source_t image, ext::number<double> dx, ext::number<double> dy) -> void;

    auto draw_image(
            detail::canvas_image_source_t image, ext::number<double> dx, ext::number<double> dy,
            ext::number<double> dw, ext::number<double> dh) -> void;

    auto draw_image(
            detail::canvas_image_source_t image, ext::number<double> sx, ext::number<double> sy,
            ext::number<double> sw, ext::number<double> sh, ext::number<double> dx,
            ext::number<double> dy, ext::number<double> dw, ext::number<double> dh) -> void;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_DRAW_IMAGE_HPP
