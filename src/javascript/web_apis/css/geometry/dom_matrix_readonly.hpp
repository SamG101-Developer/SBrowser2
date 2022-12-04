#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_READONLY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_READONLY_HPP

#include "dom_object.hpp"
#include "html/mixins/serializable.hpp"
namespace css::geometry {class dom_matrix_readonly;}
namespace css::geometry {class dom_matrix_readonly_private;}

#include INCLUDE_INNER_TYPES(css/geometry)

#include "ext/span.hpp"
#include <qmatrix4x4.h>
#include <qpointer.h>
namespace css::geometry {class dom_matrix;}
namespace css::geometry {class dom_point;}


class css::geometry::dom_matrix_readonly
        : public virtual dom_object
{
public constructors:
    dom_matrix_readonly();
    dom_matrix_readonly(ext::vector_span<ext::number<double>> init);
    MAKE_PIMPL(dom_matrix_readonly);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;
    MAKE_SERIALIZABLE;

private constructors:
    dom_matrix_readonly(QMatrix4x4 matrix);
    auto operator*(dom_matrix_readonly* other) -> dom_matrix_readonly;

public js_methods:
    static auto from_matrix(detail::dom_matrix_init_t&& other = {}) -> dom_matrix_readonly;
    static auto from_float32_array(ext::vector_span<ext::number<float>> array32) -> dom_matrix_readonly;
    static auto from_float64_array(ext::vector_span<ext::number<double>> array64) -> dom_matrix_readonly;

    auto translate(ext::number<double> tx = 0, ext::number<double> ty = 0, ext::number<double> tz = 0) const -> dom_matrix;
    auto scale(ext::number<double> sx = 1, ext::number<double> sy = 1, ext::number<double> sz = 1, ext::number<double> ox = 0, ext::number<double> oy = 0, ext::number<double> oz = 0) const -> dom_matrix;
    auto scale_non_uniform(ext::number<double> sx = 1, ext::number<double> sy = 1) const -> dom_matrix;
    auto scale3d(ext::number<double> s = 1, ext::number<double> ox = 0, ext::number<double> oy = 0, ext::number<double> oz = 0) const -> dom_matrix;
    auto rotate(ext::number<double> rx = 0, ext::number<double> ry = 0, ext::number<double> rz = 0) const -> dom_matrix;
    auto rotate_from_vector(ext::number<double> x = 0, ext::number<double> y = 0) const -> dom_matrix;
    auto rotate_axis_angle(ext::number<double> x = 0, ext::number<double> y = 0, ext::number<double> z = 0, ext::number<double> angle = 0) const -> dom_matrix;
    auto skew_x(ext::number<double> sx = 0) const -> dom_matrix;
    auto skew_y(ext::number<double> sy = 0) const -> dom_matrix;
    auto multiply(detail::dom_matrix_init_t&& other = {}) const -> dom_matrix;
    auto inverse() const -> dom_matrix;
    auto flip_x() const -> dom_matrix;
    auto flip_y() const -> dom_matrix;

    auto transform_point(detail::dom_point_init_t&& point = {}) const -> dom_point;
    auto to_float32_array() const -> ext::vector<float>;
    auto to_float64_array() const -> ext::vector<double>;;

private js_properties:
    DEFINE_GETTER(a, ext::number<double>);
    DEFINE_GETTER(b, ext::number<double>);
    DEFINE_GETTER(c, ext::number<double>);
    DEFINE_GETTER(d, ext::number<double>);
    DEFINE_GETTER(e, ext::number<double>);
    DEFINE_GETTER(f, ext::number<double>);

    DEFINE_GETTER(m11, ext::number<double>);
    DEFINE_GETTER(m12, ext::number<double>);
    DEFINE_GETTER(m13, ext::number<double>);
    DEFINE_GETTER(m14, ext::number<double>);

    DEFINE_GETTER(m21, ext::number<double>);
    DEFINE_GETTER(m22, ext::number<double>);
    DEFINE_GETTER(m23, ext::number<double>);
    DEFINE_GETTER(m24, ext::number<double>);

    DEFINE_GETTER(m31, ext::number<double>);
    DEFINE_GETTER(m32, ext::number<double>);
    DEFINE_GETTER(m33, ext::number<double>);
    DEFINE_GETTER(m34, ext::number<double>);

    DEFINE_GETTER(m41, ext::number<double>);
    DEFINE_GETTER(m42, ext::number<double>);
    DEFINE_GETTER(m43, ext::number<double>);
    DEFINE_GETTER(m44, ext::number<double>);

    DEFINE_GETTER(is_2d, ext::boolean);
    DEFINE_GETTER(is_identity, ext::boolean);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_READONLY_HPP
