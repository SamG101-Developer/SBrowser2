#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_LOCATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_LOCATION_HPP

#include "dom_object.hpp"
namespace html::other {class location;}

#include INCLUDE_INNER_TYPES(html)


class html::other::location
        : public virtual dom_object
{
private js_slots:
    ext::slot<detail::cross_origin_property_descriptor_map_t> s_cross_origin_property_descriptor_map;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_LOCATION_HPP
