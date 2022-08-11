#pragma once
#ifndef SBROWSER2_PERMISSION_STATUS_HPP
#define SBROWSER2_PERMISSION_STATUS_HPP

#include "dom/nodes/event_target.hpp"
namespace permissions {class permission_status;}

#include "_typedefs.hpp"

class permissions::permission_status
        : public dom::nodes::event_target
{
public constructors:
    permission_status();
    permission_status(detail::permissions_descriptor_t&& permission_descriptor);

public js_properties:
    ext::property<ext::string> state;
    ext::property<ext::string> name;

private js_slots:
    detail::permissions_descriptor_t s_query;
};


#endif //SBROWSER2_PERMISSION_STATUS_HPP
