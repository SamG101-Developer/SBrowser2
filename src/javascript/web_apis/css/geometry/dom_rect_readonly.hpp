#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_HPP

#include "dom_object.hpp"
#include "html/mixins/serializable.hpp"
namespace css::geometry {class dom_rect_readonly;}

#include <qrect.h>
#include USE_INNER_TYPES(css/geometry)


class css::geometry::dom_rect_readonly
        : public virtual dom_object
        , public html::mixins::serializable
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

    auto m_serialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> void override;
    auto m_deserialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> dom_rect_readonly* override;

protected cpp_properties:
    QRectF m_rect;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(x) {return m_rect.x();}
    DEFINE_CUSTOM_GETTER(y) {return m_rect.y();}
    DEFINE_CUSTOM_GETTER(w) {return m_rect.width();}
    DEFINE_CUSTOM_GETTER(h) {return m_rect.height();}

    DEFINE_CUSTOM_GETTER(top) {return m_rect.top();}
    DEFINE_CUSTOM_GETTER(right) {return m_rect.right();}
    DEFINE_CUSTOM_GETTER(bottom) {return m_rect.bottom();}
    DEFINE_CUSTOM_GETTER(left) {return m_rect.left();}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_HPP
