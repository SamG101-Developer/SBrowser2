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

public js_properties:
    ext::property<ext::string> city;
    ext::property<ext::string> country;
    ext::property<ext::string> dependant_locality;
    ext::property<ext::string> organization;
    ext::property<ext::string> phone;
    ext::property<ext::string> postal_code;
    ext::property<ext::string> recipient;
    ext::property<ext::string> region;
    ext::property<ext::string> sorting_code;
    ext::property<ext::vector<ext::string>> address_line; // TODO : const

private cpp_members:
    MAKE_PIMPL(contact_address);
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(city);
    DEFINE_CUSTOM_GETTER(country);
    DEFINE_CUSTOM_GETTER(dependant_locality);
    DEFINE_CUSTOM_GETTER(organization);
    DEFINE_CUSTOM_GETTER(phone);
    DEFINE_CUSTOM_GETTER(postal_code);
    DEFINE_CUSTOM_GETTER(recipient);
    DEFINE_CUSTOM_GETTER(region);
    DEFINE_CUSTOM_GETTER(sorting_code);
    DEFINE_CUSTOM_GETTER(address_line);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACT_ADDRESS_HPP
