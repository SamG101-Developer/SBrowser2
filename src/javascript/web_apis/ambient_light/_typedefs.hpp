#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"

namespace ambient_light_sensor::detail
{
    using ambient_light_reading_values = ext::map<ext::string, ext::any>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_AMBIENT_LIGHT__TYPEDEFS_HPP