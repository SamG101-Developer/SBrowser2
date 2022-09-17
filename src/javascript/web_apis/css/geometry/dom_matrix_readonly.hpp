#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_READONLY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_READONLY_HPP

#include "dom_object.hpp"
#include "html/mixins/serializable.hpp"
namespace css::geometry {class dom_matrix_readonly;}

#include USE_INNER_TYPES(css/geometry)
#include "ext/number.hpp"
#include <qmatrix4x4.h>
namespace css::geometry {class dom_matrix;}
namespace css::geometry {class dom_point;}


class css::geometry::dom_matrix_readonly
        : public virtual dom_object
        , public html::mixins::serializable
{
public constructors:
    dom_matrix_readonly() = default;
    dom_matrix_readonly(ext::vector_view<ext::number<double>> init);
    dom_matrix_readonly(const QMatrix4x4& other): m_matrix{other} {};

public js_methods:
    static auto from_matrix(detail::dom_matrix_init_t&& other = {}) -> dom_matrix_readonly;
    static auto from_float32_array(ext::vector_view<ext::number<float>> array32) -> dom_matrix_readonly;
    static auto from_float64_array(ext::vector_view<ext::number<double>> array64) -> dom_matrix_readonly;

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
    auto to_float64_array() const -> ext::vector<double>;

public js_properties:
    ext::property<ext::number<double>> m11;
    ext::property<ext::number<double>> m12;
    ext::property<ext::number<double>> m13;
    ext::property<ext::number<double>> m14;

    ext::property<ext::number<double>> m21;
    ext::property<ext::number<double>> m22;
    ext::property<ext::number<double>> m23;
    ext::property<ext::number<double>> m24;

    ext::property<ext::number<double>> m31;
    ext::property<ext::number<double>> m32;
    ext::property<ext::number<double>> m33;
    ext::property<ext::number<double>> m34;

    ext::property<ext::number<double>> m41;
    ext::property<ext::number<double>> m42;
    ext::property<ext::number<double>> m43;
    ext::property<ext::number<double>> m44;

    ext::property<ext::number<double>> a;
    ext::property<ext::number<double>> b;
    ext::property<ext::number<double>> c;
    ext::property<ext::number<double>> d;
    ext::property<ext::number<double>> e;
    ext::property<ext::number<double>> f;

    ext::property<ext::boolean> is_2d;
    ext::property<ext::boolean> is_identity;

public cpp_operators:
    auto operator*(const dom_matrix_readonly& other) -> dom_matrix_readonly {return dom_matrix_readonly{m_matrix * other.m_matrix};}

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
    auto to_json() const -> ext::string override;
    auto m_serialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> void override;
    auto m_deserialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> dom_matrix_readonly* override;

protected cpp_properties:
    QMatrix4x4 m_matrix;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(a) {return m11();};
    DEFINE_CUSTOM_GETTER(b) {return m12();};
    DEFINE_CUSTOM_GETTER(c) {return m13();};
    DEFINE_CUSTOM_GETTER(d) {return m14();};
    DEFINE_CUSTOM_GETTER(e) {return m21();};
    DEFINE_CUSTOM_GETTER(f) {return m22();};

    DEFINE_CUSTOM_GETTER(m11) {return m_matrix(0, 0);}
    DEFINE_CUSTOM_GETTER(m12) {return m_matrix(1, 0);}
    DEFINE_CUSTOM_GETTER(m13) {return m_matrix(2, 0);}
    DEFINE_CUSTOM_GETTER(m14) {return m_matrix(3, 0);}

    DEFINE_CUSTOM_GETTER(m21) {return m_matrix(0, 1);}
    DEFINE_CUSTOM_GETTER(m22) {return m_matrix(1, 1);}
    DEFINE_CUSTOM_GETTER(m23) {return m_matrix(2, 1);}
    DEFINE_CUSTOM_GETTER(m24) {return m_matrix(3, 1);}

    DEFINE_CUSTOM_GETTER(m31) {return m_matrix(0, 2);}
    DEFINE_CUSTOM_GETTER(m32) {return m_matrix(1, 2);}
    DEFINE_CUSTOM_GETTER(m33) {return m_matrix(2, 2);}
    DEFINE_CUSTOM_GETTER(m34) {return m_matrix(3, 2);}

    DEFINE_CUSTOM_GETTER(m41) {return m_matrix(0, 3);}
    DEFINE_CUSTOM_GETTER(m42) {return m_matrix(1, 3);}
    DEFINE_CUSTOM_GETTER(m43) {return m_matrix(2, 3);}
    DEFINE_CUSTOM_GETTER(m44) {return m_matrix(3, 3);}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_READONLY_HPP
