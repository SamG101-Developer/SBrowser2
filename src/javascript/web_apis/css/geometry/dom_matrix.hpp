#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_HPP

#include "css/geometry/dom_matrix_readonly.hpp"
namespace css::geometry {class dom_matrix;}

#include "qmatrix4x4.h"
#include USE_INNER_TYPES(css/geometry)


class css::geometry::dom_matrix
        : public dom_matrix_readonly
{
public constructors:
    using dom_matrix_readonly::dom_matrix_readonly;
    dom_matrix(QMatrix4x4 other) {m_matrix = other;};

public js_methods:
    static auto from_matrix(detail::dom_matrix_init_t&& other = {}) -> dom_matrix;
    static auto from_float32_array(ext::vector_view<ext::number<float>> array32) -> dom_matrix;
    static auto from_float64_array(ext::vector_view<ext::number<double>> array64) -> dom_matrix;

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

public cpp_operators:
    auto operator*=(const dom_matrix_readonly& other) -> dom_matrix& {m_matrix *= other.m_matrix; return *this;}

public cpp_methods:
    auto m_serialize(ext::map<ext::string, ext::any> &serialized, ext::boolean &&for_storage) -> void override;
    auto m_deserialize(ext::map<ext::string, ext::any> &serialized, ext::boolean &&for_storage) -> dom_matrix* override;

private cpp_accessors:
    DEFINE_SETTER(m11) {m_matrix(0, 0) = *val;}
    DEFINE_SETTER(m12) {m_matrix(1, 0) = *val;}
    DEFINE_SETTER(m13) {m_matrix(2, 0) = *val;}
    DEFINE_SETTER(m14) {m_matrix(3, 0) = *val;}

    DEFINE_SETTER(m21) {m_matrix(0, 1) = *val;}
    DEFINE_SETTER(m22) {m_matrix(1, 1) = *val;}
    DEFINE_SETTER(m23) {m_matrix(2, 1) = *val;}
    DEFINE_SETTER(m24) {m_matrix(3, 1) = *val;}

    DEFINE_SETTER(m31) {m_matrix(0, 2) = *val;}
    DEFINE_SETTER(m32) {m_matrix(1, 2) = *val;}
    DEFINE_SETTER(m33) {m_matrix(2, 2) = *val;}
    DEFINE_SETTER(m34) {m_matrix(3, 2) = *val;}

    DEFINE_SETTER(m41) {m_matrix(0, 3) = *val;}
    DEFINE_SETTER(m42) {m_matrix(1, 3) = *val;}
    DEFINE_SETTER(m43) {m_matrix(2, 3) = *val;}
    DEFINE_SETTER(m44) {m_matrix(3, 3) = *val;}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_HPP
