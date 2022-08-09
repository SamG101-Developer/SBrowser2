#pragma once
#ifndef SBROWSER2_PERMISSIONS_HPP
#define SBROWSER2_PERMISSIONS_HPP

#include "dom_object.hpp"
namespace permissions {class permission;}

#include <future>
namespace permissions {class permission_status;}


class permissions::permission
        : public virtual dom_object
{
public js_properties:
    auto query(dom_object* permission_description) -> ext::property<std::promise<permission_status*>>;
};


#endif //SBROWSER2_PERMISSIONS_HPP
