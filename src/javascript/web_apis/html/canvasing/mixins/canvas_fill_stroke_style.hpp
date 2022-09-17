#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_FILL_STROKE_STYLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_FILL_STROKE_STYLE_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_fill_stroke_style;}

#include USE_INNER_TYPES(html)
namespace html::canvasing {class canvas_gradient;}
namespace html::canvasing {class canvas_pattern;}


class html::canvasing::mixins::canvas_fill_stroke_style
        : public virtual dom_object
{
public enums:
    enum class canvas_pattern_repeat_t {_, REPEAT, REPEAT_X, REPEAT_Y, NO_REPEAT};

public constructors:
    ~canvas_fill_stroke_style();

public js_methods:
    auto create_linear_gradient(ext::number<double> x0, ext::number<double> x1, ext::number<double> y0, ext::number<double> y1) -> canvas_gradient;
    auto create_radial_gradient(ext::number<double> x0, ext::number<double> x1, ext::number<double> y0, ext::number<double> y1, ext::number<double> r0, ext::number<double> r1) -> canvas_gradient;
    auto create_conic_gradient(ext::number<double> start_angle, ext::number<double> x, ext::number<double> y) -> canvas_gradient;
    auto create_pattern(detail::canvas_image_source_t&& image, canvas_pattern_repeat_t repetition) -> canvas_pattern;

public js_properties:
    ext::property<ext::variant<ext::string, canvas_gradient*, canvas_pattern*>> fill_style;
    ext::property<ext::variant<ext::string, canvas_gradient*, canvas_pattern*>> stroke_style;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(fill_style);
    DEFINE_CUSTOM_GETTER(stroke_style);

    DEFINE_CUSTOM_SETTER(fill_style);
    DEFINE_CUSTOM_SETTER(stroke_style);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_FILL_STROKE_STYLE_HPP
