#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_TRANSFORM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_TRANSFORM_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_transform;}

namespace css::geometry {class dom_matrix;}


class html::canvasing::mixins::canvas_transform
        : public virtual dom_object
{
public js_methods:
    auto scale(const ext::number<double>& x, const ext::number<double>& y) -> void;
    auto rotate(const ext::number<double>& angle) -> void;
    auto translate(const ext::number<double>& x, const ext::number<double>& y) -> void;
    auto transform(const ext::number<double>& a, const ext::number<double>& b, const ext::number<double>& c, const ext::number<double>& d, const ext::number<double>& e, const ext::number<double>& f) -> void;

    auto transform() -> css::geometry::dom_matrix;
    auto set_transform(const ext::number<double>& a, const ext::number<double>& b, const ext::number<double>& c, const ext::number<double>& d, const ext::number<double>& e, const ext::number<double>& f) -> void;
    auto reset_transform() -> void;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_TRANSFORM_HPP
