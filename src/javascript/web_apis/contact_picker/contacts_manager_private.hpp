#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACTS_MANAGER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACTS_MANAGER_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(contact_picker)
#include "ext/vector.hpp"


DEFINE_PRIVATE_CLASS(contact_picker, contacts_manager)
        : virtual dom_object_private
{
    MAKE_QIMPL(contacts_manager);
    ext::vector<detail::user_contact_t*> available_contacts;
    ext::vector<detail::contact_property_t> supported_properties;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACTS_MANAGER_PRIVATE_HPP
