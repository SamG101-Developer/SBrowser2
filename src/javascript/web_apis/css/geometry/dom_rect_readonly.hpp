#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_HPP

#include "dom_object.hpp"
#include "html/mixins/serializable.hpp"
namespace css::geometry {class dom_rect_readonly;}

#include <qrect.h>
#include INCLUDE_INNER_TYPES(css/geometry)


class css::geometry::dom_rect_readonly
        : public virtual dom_object
        , public html::mixins::serializable
{
public constructors:
    dom_rect_readonly(ext::number<double> x = 0, ext::number<double> y = 0, ext::number<double> w = 0, ext::number<double> h = 0);

public js_methods:
    static auto from_rect(detail::dom_rect_init_t&& other = {}) -> dom_rect_readonly;

private js_properties:
    ext::property<ext::number<double>> x;
    ext::property<ext::number<double>> y;
    ext::property<ext::number<double>> w;
    ext::property<ext::number<double>> h;

    ext::property<ext::number<double>> top;
    ext::property<ext::number<double>> right;
    ext::property<ext::number<double>> bottom;
    ext::property<ext::number<double>> left;

public cpp_members:
    MAKE_PIMPL_QT_PROTECTED(QRectF);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;

    auto m_serialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> void override;
    auto m_deserialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> dom_rect_readonly* override;

private js_properties:
    DEFINE_CUSTOM_GETTER(x) {return d_ptr->x();}
    DEFINE_CUSTOM_GETTER(y) {return d_ptr->y();}
    DEFINE_CUSTOM_GETTER(w) {return d_ptr->width();}
    DEFINE_CUSTOM_GETTER(h) {return d_ptr->height();}

    DEFINE_CUSTOM_GETTER(top) {return d_ptr->top();}
    DEFINE_CUSTOM_GETTER(right) {return d_ptr->right();}
    DEFINE_CUSTOM_GETTER(bottom) {return d_ptr->bottom();}
    DEFINE_CUSTOM_GETTER(left) {return d_ptr->left();}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_HPP
