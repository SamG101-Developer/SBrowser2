#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_3DS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_3DS__TYPEDEFS_HPP



#include "ext/string.hpp"

namespace three_ds::detail
{
    enum class three_ds_challenge_ind {REQUESTED, MANDATED, NONE};

    using three_ds_request = ext::map<ext::string, ext::any>;
    using three_ds_response = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_3DS__TYPEDEFS_HPP
