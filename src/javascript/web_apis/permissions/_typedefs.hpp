#ifndef SBROWSER2_PERMISSIONS__TYPEDEFS_HPP
#define SBROWSER2_PERMISSIONS__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.ixx"
#include "ext/string.hpp"

namespace permissions {class permission_status;}

namespace permissions::detail
{
    enum class permission_state_t {DENIED, GRANTED, PROMPT};
    struct powerful_feature_t;
    using permissions_descriptor_t = ext::map<ext::string, ext::any>;
    using permissions_result_t = permission_status;
    using extra_permission_data_t = permission_state_t;
}

#endif //SBROWSER2_PERMISSIONS__TYPEDEFS_HPP
