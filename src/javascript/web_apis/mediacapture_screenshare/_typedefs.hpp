#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_SCREENSHARE__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_SCREENSHARE__TYPEDEFS_HPP



#include "ext/string.hpp"


namespace mediacapture::detail
{
    using display_media_stream_options_t = ext::map<ext::string, ext::any>;

    enum class self_capture_preference_enum_t {INCLUDE, EXCLUDE};
    enum class system_audio_preference_enum_t {INCLUDE, EXCLUDE};
    enum class surface_switching_preference_enum_t {INCLUDE, EXCLUDE};
    enum display_capture_surface_type_t {MONITOR, WINDOW, BROWSER};
    enum cursor_capture_constraint_t {NEVER, ALWAYS, MOTION};
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_SCREENSHARE__TYPEDEFS_HPP
