#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_HPP

#include "css/geometry/dom_rect_readonly.hpp"
namespace css::geometry {class dom_rect;}
namespace css::geometry {class dom_rect_private;}


class css::geometry::dom_rect
        : public dom_rect_readonly
{
public constructors:
    using dom_rect_readonly::dom_rect_readonly;
    MAKE_PIMPL(dom_rect);
    MAKE_V8_AVAILABLE(ALL); // TODO
    MAKE_STRINGIFIER;
    MAKE_SERIALIZABLE;

public js_methods:
    static auto from_rect(detail::dom_rect_init_t&& other = {}) -> dom_rect;

private js_properties:
    DEFINE_SETTER(x, ext::number<double>);
    DEFINE_SETTER(y, ext::number<double>);
    DEFINE_SETTER(w, ext::number<double>);
    DEFINE_SETTER(h, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_HPP
