#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_POINT_READONLY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_POINT_READONLY_HPP

#include "dom_object.hpp"
#include "html/mixins/serializable.hpp"
namespace css::geometry {class dom_point_readonly;}

#include "ext/number.hpp"
#include <qvectornd.h>
#include USE_INNER_TYPES(css/geometry)
namespace css::geometry {class dom_point;}


class css::geometry::dom_point_readonly
        : public dom_object
        , public html::mixins::serializable
{
public constructors:
    dom_point_readonly() = default;
    dom_point_readonly(ext::number<double> x = 0, ext::number<double> y = 0, ext::number<double> z = 0, ext::number<double> w = 0);

public js_methods:
    static auto from_point(detail::dom_point_init_t&& other = {}) -> dom_point_readonly;
    auto matrix_transform(detail::dom_matrix_init_t&& matrix = {}) -> dom_point;

public js_properties:
    ext::property<ext::number<double>> x;
    ext::property<ext::number<double>> y;
    ext::property<ext::number<double>> z;
    ext::property<ext::number<double>> w;

public cpp_methods:
    auto to_json() const -> ext::string override;
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
    auto m_serialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> void override;
    auto m_deserialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> dom_point_readonly* override;


protected cpp_properties:
    QVector4D m_point;

private cpp_properties:
    DEFINE_CUSTOM_GETTER(x) {return m_point.x();};
    DEFINE_CUSTOM_GETTER(y) {return m_point.y();};
    DEFINE_CUSTOM_GETTER(z) {return m_point.z();};
    DEFINE_CUSTOM_GETTER(w) {return m_point.w();};
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_POINT_READONLY_HPP
