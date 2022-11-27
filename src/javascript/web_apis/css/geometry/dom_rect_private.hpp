#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "css/geometry/dom_rect_readonly_private.hpp"


DEFINE_PRIVATE_CLASS(css::geometry, dom_rect) : css::geometry::dom_rect_readonly_private
{
    MAKE_QIMPL(dom_rect);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_PRIVATE_HPP
