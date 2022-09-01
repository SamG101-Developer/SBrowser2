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
            detail::canvas_image_source_t image, const ext::number<double>& dx, const ext::number<double>& dy) -> void;

    auto draw_image(
            detail::canvas_image_source_t image, const ext::number<double>& dx, const ext::number<double>& dy,
            const ext::number<double>& dw, const ext::number<double>& dh) -> void;

    auto draw_image(
            detail::canvas_image_source_t image, const ext::number<double>& sx, const ext::number<double>& sy,
            const ext::number<double>& sw, const ext::number<double>& sh, const ext::number<double>& dx,
            const ext::number<double>& dy, const ext::number<double>& dw, const ext::number<double>& dh) -> void;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_DRAW_IMAGE_HPP
