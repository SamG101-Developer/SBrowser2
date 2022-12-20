module;
#include "ext/macros/pimpl.hpp"


export module apis.contact_picker.contacts_manager_private;
import apis.dom_object_private;

import ext.vector;


DEFINE_PRIVATE_CLASS(contact_picker, contacts_manager)
        : virtual dom_object_private
{
    MAKE_QIMPL(contacts_manager);
    ext::vector<detail::user_contact_t*> available_contacts;
    ext::vector<detail::contact_property_t> supported_properties;
};
