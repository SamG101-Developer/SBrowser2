module;
#include "ext/macros/macros.hpp"


export module apis.contact_picker.contacts_manager_private;
import apis.dom_object_private;

import apis.contact_picker.types;
import ext.core;


DEFINE_PRIVATE_CLASS(contact_picker, contacts_manager)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(contacts_manager);

public:
    ext::vector<detail::user_contact_t*> available_contacts;
    ext::vector<detail::contact_property_t> supported_properties;
};
