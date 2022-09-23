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

public cpp_members:
    auto m_serialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> void override;
    auto m_deserialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> dom_rect* override;

private js_properties:
    DEFINE_CUSTOM_SETTER(x) {d_ptr->setX(*val);};
    DEFINE_CUSTOM_SETTER(y) {d_ptr->setY(*val);};
    DEFINE_CUSTOM_SETTER(w) {d_ptr->setWidth(*val);};
    DEFINE_CUSTOM_SETTER(h) {d_ptr->setHeight(*val);};
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_HPP
