#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACT_ADDRESS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACT_ADDRESS_HPP

#include "dom_object.hpp"
namespace contact_picker {class contact_address;}

#include USE_INNER_TYPES(contact_picker)


class contact_picker::contact_address
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(contact_address);
    contact_address() = default;

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
    ext::property<const ext::vector<ext::string>> address_line;

private:
    std::unique_ptr<detail::physical_address_t> m_address;

private cpp_accessors:
    DEFINE_GETTER(city);
    DEFINE_GETTER(country);
    DEFINE_GETTER(dependant_locality);
    DEFINE_GETTER(organization);
    DEFINE_GETTER(phone);
    DEFINE_GETTER(postal_code);
    DEFINE_GETTER(recipient);
    DEFINE_GETTER(region);
    DEFINE_GETTER(sorting_code);
    DEFINE_GETTER(address_line);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACT_ADDRESS_HPP
