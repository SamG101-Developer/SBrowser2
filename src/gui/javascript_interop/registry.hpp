#ifndef SBROWSER2_REGISTRY_HPP
#define SBROWSER2_REGISTRY_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"


namespace gui::javascript_interop
{
    auto permission_request_popup(
            ext::string&& permission)
            -> ext::boolean;
};


#endif //SBROWSER2_REGISTRY_HPP
