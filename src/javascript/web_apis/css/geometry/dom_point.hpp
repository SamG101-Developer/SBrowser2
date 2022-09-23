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

public cpp_members:
    MAKE_V8_AVAILABLE;

    auto m_serialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> void override;
    auto m_deserialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> dom_point* override;


private js_properties:
    DEFINE_CUSTOM_SETTER(x) {d_ptr->setX(*val.as<float>());};
    DEFINE_CUSTOM_SETTER(y) {d_ptr->setY(*val.as<float>());};
    DEFINE_CUSTOM_SETTER(z) {d_ptr->setZ(*val.as<float>());};
    DEFINE_CUSTOM_SETTER(w) {d_ptr->setW(*val.as<float>());};
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_POINT_HPP
