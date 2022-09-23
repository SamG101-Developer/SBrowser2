#pragma once
#ifndef SBROWSER2_PERMISSIONS_HPP
#define SBROWSER2_PERMISSIONS_HPP

#include "dom_object.hpp"
namespace permissions {class permission;}

#include "ext/map.hpp"
#include "ext/promise.hpp"
#include INCLUDE_INNER_TYPES(permissions)
namespace permissions {class permission_status;}


class permissions::permission
        : public virtual dom_object
{
private js_properties:
    auto query(detail::permissions_descriptor_t&& permission_descriptor) -> ext::promise<permission_status*>;
};


#endif //SBROWSER2_PERMISSIONS_HPP
