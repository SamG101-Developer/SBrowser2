#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACT_ADDRESS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACT_ADDRESS_HPP

#include "dom_object.hpp"
namespace contact_picker {class contact_address;}

#include "contact_picker/contact_address_private.hpp"


class contact_picker::contact_address
        : public virtual dom_object
{
public constructors:
    contact_address();
    MAKE_PIMPL(contact_address);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(city, ext::string);
    DEFINE_GETTER(country, ext::string);
    DEFINE_GETTER(dependant_locality, ext::string);
    DEFINE_GETTER(organization, ext::string);
    DEFINE_GETTER(phone, ext::string);
    DEFINE_GETTER(postal_code, ext::string);
    DEFINE_GETTER(recipient, ext::string);
    DEFINE_GETTER(region, ext::string);
    DEFINE_GETTER(sorting_code, ext::string);
    DEFINE_GETTER(address_line, ext::vector<ext::string>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACT_ADDRESS_HPP
