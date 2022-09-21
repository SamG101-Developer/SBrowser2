#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"


namespace contact_picker::detail
{
    struct physical_address_t;
    struct user_contact_t;
    struct contact_source_t;

    enum class contact_property_t {ADDRESS, EMAIL, ICON, NAME, TEL};

    using contact_info_t = ext::map<ext::string, ext::any>;
    using contacts_select_options_t = ext::map<ext::string, ext::any>;
    using contact_address_t = physical_address_t;
    using contacts_manager_t = contact_source_t;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER__TYPEDEFS_HPP
