#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_HPP

#include "dom_object.hpp"
namespace css::geometry {class dom_rect_readonly;}
namespace css::geometry {class dom_rect_readonly_private;}

#include INCLUDE_INNER_TYPES(css/geometry)


class css::geometry::dom_rect_readonly
        : public virtual dom_object
{
public constructors:
    dom_rect_readonly(ext::number<double> x = 0, ext::number<double> y = 0, ext::number<double> w = 0, ext::number<double> h = 0);
    dom_rect_readonly(QRectF rectangle);
    MAKE_PIMPL(dom_rect_readonly);
    MAKE_V8_AVAILABLE(ALL); // TODO
    MAKE_STRINGIFIER;
    MAKE_SERIALIZABLE;

public js_methods:
    static auto from_rect(detail::dom_rect_init_t&& other = {}) -> dom_rect_readonly;

private js_properties:
    DEFINE_GETTER(x, ext::number<double>);
    DEFINE_GETTER(y, ext::number<double>);
    DEFINE_GETTER(w, ext::number<double>);
    DEFINE_GETTER(h, ext::number<double>);

    DEFINE_GETTER(top, ext::number<double>);
    DEFINE_GETTER(right, ext::number<double>);
    DEFINE_GETTER(bottom, ext::number<double>);
    DEFINE_GETTER(left, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_HPP
