#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION__TYPEDEFS_HPP

#include "ext/string.hpp"


namespace presentation::detail
{
    struct presentation_display_t;

    enum class presentation_connection_state_t {CONNECTING, CONNECTED, CLOSED, TERMINATED};

    using presentation_id = ext::string;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION__TYPEDEFS_HPP
