#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_IMAGE_SMOOTHING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_IMAGE_SMOOTHING_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_image_smoothing;}

#include USE_INNER_TYPES(html)


class html::canvasing::mixins::canvas_image_smoothing
        : public virtual dom_object
{
public js_properties:
    ext::property<ext::boolean> image_smoothing_enabled;
    ext::property<detail::image_smoothing_quality_t> global_composite_operation;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_IMAGE_SMOOTHING_HPP
