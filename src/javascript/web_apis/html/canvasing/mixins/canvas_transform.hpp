#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_TRANSFORM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_TRANSFORM_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_transform;}

#include INCLUDE_INNER_TYPES(css/geometry)
#include INCLUDE_INNER_TYPES(html)
namespace css::geometry {class dom_matrix;}


class html::canvasing::mixins::canvas_transform
        : public virtual dom_object
{
public js_methods:
    auto scale(ext::number<double> x, ext::number<double> y) -> void;
    auto rotate(ext::number<double> angle) -> void;
    auto translate(ext::number<double> x, ext::number<double> y) -> void;
    auto transform(ext::number<double> a, ext::number<double> b, ext::number<double> c, ext::number<double> d, ext::number<double> e, ext::number<double> f) -> void;

    auto get_transform() -> css::geometry::dom_matrix*;
    auto set_transform(ext::number<double> a, ext::number<double> b, ext::number<double> c, ext::number<double> d, ext::number<double> e, ext::number<double> f) -> void;
    auto set_transform(css::detail::dom_matrix_init_t&& other = {}) -> void;
    auto reset_transform() -> void;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    std::unique_ptr<css::geometry::dom_matrix> m_current_transform_matrix;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_TRANSFORM_HPP
