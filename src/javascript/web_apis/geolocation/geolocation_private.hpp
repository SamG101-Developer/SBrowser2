#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_DETAIL_GEOLOCATION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_DETAIL_GEOLOCATION_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include "ext/vector.hpp"

namespace geolocation {class geolocation_position;}


DEFINE_PRIVATE_CLASS(geolocation, geolocation) : virtual dom_object_private
{
    geolocation_position* cached_position;
    ext::vector<ext::number<ulong>> watch_ids;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION_DETAIL_GEOLOCATION_PRIVATE_HPP
