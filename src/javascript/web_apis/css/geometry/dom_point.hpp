#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_POINT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_POINT_HPP

#include "css/geometry/dom_point_readonly.hpp"
namespace css::geometry {class dom_point_readonly;}


class css::geometry::dom_point
        : public dom_point_readonly
{
public constructors:
    using dom_point_readonly::dom_point_readonly;

public js_methods:
    static auto from_point(detail::dom_point_init_t&& other = {}) -> dom_point;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_accessors:
    DEFINE_SETTER(x) {m_point.setX(*val.as<float>());};
    DEFINE_SETTER(y) {m_point.setY(*val.as<float>());};
    DEFINE_SETTER(z) {m_point.setZ(*val.as<float>());};
    DEFINE_SETTER(w) {m_point.setW(*val.as<float>());};
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_POINT_HPP
