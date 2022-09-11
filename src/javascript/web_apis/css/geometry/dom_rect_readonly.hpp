#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_HPP

#include "dom_object.hpp"
namespace css::geometry {class dom_rect_readonly;}

#include <qrect.h>
#include USE_INNER_TYPES(css/geometry)


class css::geometry::dom_rect_readonly
        : public virtual dom_object
{
public constructors:
    dom_rect_readonly(ext::number<double> x = 0, ext::number<double> y = 0, ext::number<double> w = 0, ext::number<double> h = 0);

public js_methods:
    static auto from_rect(detail::dom_rect_init_t&& other = {}) -> dom_rect_readonly;

public js_properties:
    ext::property<ext::number<double>> x;
    ext::property<ext::number<double>> y;
    ext::property<ext::number<double>> w;
    ext::property<ext::number<double>> h;

    ext::property<ext::number<double>> top;
    ext::property<ext::number<double>> right;
    ext::property<ext::number<double>> bottom;
    ext::property<ext::number<double>> left;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
    auto to_json() const -> ext::string override;

protected cpp_properties:
    QRectF m_rect;

private cpp_accessors:
    DEFINE_GETTER(x) {return m_rect.x();}
    DEFINE_GETTER(y) {return m_rect.y();}
    DEFINE_GETTER(w) {return m_rect.width();}
    DEFINE_GETTER(h) {return m_rect.height();}

    DEFINE_GETTER(top) {return m_rect.top();}
    DEFINE_GETTER(right) {return m_rect.right();}
    DEFINE_GETTER(bottom) {return m_rect.bottom();}
    DEFINE_GETTER(left) {return m_rect.left();}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_HPP
