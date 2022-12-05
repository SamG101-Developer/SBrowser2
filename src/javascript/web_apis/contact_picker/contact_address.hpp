#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACT_ADDRESS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACT_ADDRESS_HPP


namespace contact_picker {class contact_address;}
namespace contact_picker {class contact_address_private;}


class contact_picker::contact_address
        : public virtual dom_object
{
public constructors:
    contact_address();
    MAKE_PIMPL(contact_address);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(city, ext::string_view);
    DEFINE_GETTER(country, ext::string_view);
    DEFINE_GETTER(dependant_locality, ext::string_view);
    DEFINE_GETTER(organization, ext::string_view);
    DEFINE_GETTER(phone, ext::string_view);
    DEFINE_GETTER(postal_code, ext::string_view);
    DEFINE_GETTER(recipient, ext::string_view);
    DEFINE_GETTER(region, ext::string_view);
    DEFINE_GETTER(sorting_code, ext::string_view);
    DEFINE_GETTER(address_line, ext::vector<ext::string>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACT_ADDRESS_HPP
