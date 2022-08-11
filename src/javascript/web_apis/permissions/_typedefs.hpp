#ifndef SBROWSER2__TYPEDEFS_HPP
#define SBROWSER2__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"

namespace permissions {class permission_status;}

namespace permissions::detail
{
    enum class permission_state_t {DENIED, GRANTED, PROMPT};

    using permissions_descriptor_t = ext::map<ext::string, ext::any>;
    using permissions_result_t = permission_status;
    using extra_permission_data_t = permission_state_t;
}

#endif //SBROWSER2__TYPEDEFS_HPP
