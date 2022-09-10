#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_QUAD_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_QUAD_HPP

#include "dom_object.hpp"
namespace css::geometry {class dom_quad;}

#include USE_INNER_TYPES(css/geometry)
namespace css::geometry {class dom_point;}


class css::geometry::dom_quad
        : public virtual dom_object
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

public cpp_methods:

};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_QUAD_HPP
