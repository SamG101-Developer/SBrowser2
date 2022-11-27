#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include <qrect.h>


DEFINE_PRIVATE_CLASS(css::geometry, dom_rect_readonly) : virtual dom_object_private
{
    QRectF rect;

    auto map_to(dom_rect_readonly* other) const -> std::unique_ptr<dom_rect_readonly>;
    auto intersected_with(dom_rect_readonly* other) const -> std::unique_ptr<dom_rect_readonly>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_RECT_READONLY_PRIVATE_HPP
