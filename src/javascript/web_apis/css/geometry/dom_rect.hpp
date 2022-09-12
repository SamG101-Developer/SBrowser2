#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_HPP

#include "css/geometry/dom_rect_readonly.hpp"
#include "html/mixins/serializable.hpp"
namespace css::geometry {class dom_rect;}


class css::geometry::dom_rect
        : public dom_rect_readonly
{
public constructors:
    using dom_rect_readonly::dom_rect_readonly;

public js_methods:
    static auto from_rect(detail::dom_rect_init_t&& other = {}) -> dom_rect;

public cpp_methods:
    auto m_serialize(ext::map<ext::string, ext::any> &serialized, ext::boolean &&for_storage) -> void override;
    auto m_deserialize(ext::map<ext::string, ext::any> &serialized, ext::boolean &&for_storage) -> dom_rect* override;

private cpp_accessors:
    DEFINE_SETTER(x) {m_rect.setX(*val);};
    DEFINE_SETTER(y) {m_rect.setY(*val);};
    DEFINE_SETTER(w) {m_rect.setWidth(*val);};
    DEFINE_SETTER(h) {m_rect.setHeight(*val);};
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_HPP
