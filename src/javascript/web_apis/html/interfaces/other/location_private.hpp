#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_LOCATION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_LOCATION_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(html)


DEFINE_PRIVATE_CLASS(html::others, location) : dom_object_private
{
    detail::cross_origin_property_descriptor_map_t cross_origin_property_descriptor_map;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_LOCATION_PRIVATE_HPP
