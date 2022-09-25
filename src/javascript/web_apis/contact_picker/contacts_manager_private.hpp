#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACTS_MANAGER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACTS_MANAGER_PRIVATE_HPP

#include "dom_object_private.hpp"

#include "ext/pimpl.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(contact_picker)


DEFINE_PRIVATE_CLASS(contact_picker, contacts_manager) : virtual dom_object_private
{
    ext::vector<detail::user_contact_t*> available_contacts;
    ext::vector<detail::contact_property_t> supported_properties;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACTS_MANAGER_PRIVATE_HPP
