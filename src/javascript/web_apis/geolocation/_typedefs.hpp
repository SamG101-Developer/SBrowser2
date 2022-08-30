#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"

namespace geolocation {class geolocation_position;}
namespace geolocation {class geolocation_position_error;}


namespace geolocation::detail
{
    enum class error_reason_t {PERMISSION_DENIED, POSITION_UNAVAILABLE, TIMEOUT};

    using position_error_callback_t = ext::function<void(geolocation_position_error* position)>;
    using position_callback_t = ext::function<void(geolocation_position* position)>;
    using position_options_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GEOLOCATION__TYPEDEFS_HPP
