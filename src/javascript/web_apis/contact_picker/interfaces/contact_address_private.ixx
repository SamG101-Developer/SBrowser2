module;
#include "ext/macros.hpp"


export module apis.contact_picker.contact_address:p;
import apis.dom_object;

import apis.contact_picker.types;


DEFINE_PRIVATE_CLASS(contact_picker, contact_address) final
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(contact_address);

public:
    std::unique_ptr<detail::physical_address_t> address;
};
