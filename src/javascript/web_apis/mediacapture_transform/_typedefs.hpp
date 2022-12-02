#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.ixx"
#include "ext/string.hpp"

namespace mediacapture::detail
{
    using media_stream_track_processor_init_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM__TYPEDEFS_HPP
