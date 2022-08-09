#pragma once
#ifndef SBROWSER2_PERMISSION_STATUS_HPP
#define SBROWSER2_PERMISSION_STATUS_HPP

#include "dom/nodes/event_target.hpp"
namespace permissions {class permission_status;}

class permissions::permission_status
        : public dom::nodes::event_target
{
public constructors:
    permission_status();

public js_properties:
    ext::property<ext::string> state;
    ext::property<ext::string> name;
};


#endif //SBROWSER2_PERMISSION_STATUS_HPP
