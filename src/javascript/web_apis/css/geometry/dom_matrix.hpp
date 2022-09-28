#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_HPP

#include "css/geometry/dom_matrix_readonly.hpp"
namespace css::geometry {class dom_matrix;}

#include "qmatrix4x4.h"
#include "qpointer.h"
#include INCLUDE_INNER_TYPES(css/geometry)

#include "dom_matrix_private.hpp"


class css::geometry::dom_matrix
        : public dom_matrix_readonly
{
public constructors:
    using dom_matrix_readonly::dom_matrix_readonly;
    MAKE_PIMPL(dom_matrix);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;
    MAKE_SERIALIZABLE;

public js_methods:
    static auto from_matrix(detail::dom_matrix_init_t&& other = {}) -> dom_matrix;
    static auto from_float32_array(std::initializer_list<ext::number<float>> array32) -> dom_matrix;
    static auto from_float64_array(std::initializer_list<ext::number<double>> array64) -> dom_matrix;

    auto multiply_self(detail::dom_matrix_init_t&& other = {}) -> dom_matrix;
    auto pre_multiply_self(detail::dom_matrix_init_t&& other = {}) -> dom_matrix;
    auto translate_self(ext::number<double> tx = 0, ext::number<double> ty = 0, ext::number<double> tz = 0) const -> dom_matrix;
    auto scale_self(ext::number<double> sx = 1, ext::number<double> sy = 1, ext::number<double> sz = 1, ext::number<double> ox = 0, ext::number<double> oy = 0, ext::number<double> oz = 0) const -> dom_matrix;
    auto scale3d_self(ext::number<double> s = 1, ext::number<double> ox = 0, ext::number<double> oy = 0, ext::number<double> oz = 0) const -> dom_matrix;
    auto rotate_self(ext::number<double> rx = 0, ext::number<double> ry = 0, ext::number<double> rz = 0) const -> dom_matrix;
    auto rotate_from_vector_self(ext::number<double> x = 0, ext::number<double> y = 0) const -> dom_matrix;
    auto rotate_axis_angle_self(ext::number<double> x = 0, ext::number<double> y = 0, ext::number<double> z = 0, ext::number<double> angle = 0) const -> dom_matrix;
    auto skew_x_self(ext::number<double> sx = 0) const -> dom_matrix;
    auto skew_y_self(ext::number<double> sy = 0) const -> dom_matrix;
    auto invert_self() -> dom_matrix;

private cpp_members:
    auto operator*=(dom_matrix_readonly* other) -> dom_matrix&;

private js_properties:
    DEFINE_SETTER(m11, ext::number<double>);
    DEFINE_SETTER(m12, ext::number<double>);
    DEFINE_SETTER(m13, ext::number<double>);
    DEFINE_SETTER(m14, ext::number<double>);

    DEFINE_SETTER(m21, ext::number<double>);
    DEFINE_SETTER(m22, ext::number<double>);
    DEFINE_SETTER(m23, ext::number<double>);
    DEFINE_SETTER(m24, ext::number<double>);

    DEFINE_SETTER(m31, ext::number<double>);
    DEFINE_SETTER(m32, ext::number<double>);
    DEFINE_SETTER(m33, ext::number<double>);
    DEFINE_SETTER(m34, ext::number<double>);

    DEFINE_SETTER(m41, ext::number<double>);
    DEFINE_SETTER(m42, ext::number<double>);
    DEFINE_SETTER(m43, ext::number<double>);
    DEFINE_SETTER(m44, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_HPP
