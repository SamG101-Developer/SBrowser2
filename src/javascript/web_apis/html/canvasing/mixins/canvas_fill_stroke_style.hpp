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
public constructors:
    ~canvas_fill_stroke_style();

public js_methods:
    auto create_linear_gradient(ext::number<double>&& x0, ext::number<double>&& x1, ext::number<double>&& y0, ext::number<double>&& y1) -> canvas_gradient;
    auto create_radial_gradient(ext::number<double>&& x0, ext::number<double>&& x1, ext::number<double>&& y0, ext::number<double>&& y1, ext::number<double>&& r0, ext::number<double>&& r1) -> canvas_gradient;
    auto create_conic_gradient(ext::number<double>&& angle, ext::number<double>&& x, ext::number<double>&& y) -> canvas_gradient;
    auto create_pattern(detail::canvas_image_source_t&& image, ext::string&& repetition) -> canvas_pattern;

public js_properties:
    ext::variant<ext::string, canvas_gradient*, canvas_pattern*> stroke_style;
    ext::variant<ext::string, canvas_gradient*, canvas_pattern*> fill_style;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_FILL_STROKE_STYLE_HPP
