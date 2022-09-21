#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_QUAD_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_QUAD_HPP

#include "dom_object.hpp"
#include "html/mixins/serializable.hpp"
namespace css::geometry {class dom_quad;}

#include <qpolygon.h>
#include USE_INNER_TYPES(css/geometry)
namespace css::geometry {class dom_point;}
namespace css::geometry {class dom_rect;}


class css::geometry::dom_quad
        : public virtual dom_object
        , public html::mixins::serializable
{
public constructors:
    dom_quad(detail::dom_point_init_t&& p1 = {}, detail::dom_point_init_t&& p2 = {}, detail::dom_point_init_t&& p3 = {}, detail::dom_point_init_t&& p4 = {});

public js_methods:
    static auto from_rect(detail::dom_rect_init_t&& other = {}) -> dom_quad;
    static auto from_quad(detail::dom_quad_init_t&& other = {}) -> dom_quad;
    auto get_bouunds() -> dom_rect;

public js_properties:
    ext::property<std::unique_ptr<dom_point>> p1;
    ext::property<std::unique_ptr<dom_point>> p2;
    ext::property<std::unique_ptr<dom_point>> p3;
    ext::property<std::unique_ptr<dom_point>> p4;

public cpp_members:
    MAKE_PIMPL_QT(QPolygonF);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;

    auto m_serialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> void override;
    auto m_deserialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> dom_quad* override;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(p1);
    DEFINE_CUSTOM_GETTER(p2);
    DEFINE_CUSTOM_GETTER(p3);
    DEFINE_CUSTOM_GETTER(p4);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_QUAD_HPP
