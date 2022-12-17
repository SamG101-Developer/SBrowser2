module;
#include <memory>


export module apis.contact_picker.types;

import ext.any;
import ext.map;
import ext.string;
import ext.vector;

namespace file_api {class blob;}


export namespace contact_picker::detail
{
    struct physical_address_t;
    struct user_contact_t;
    struct contact_source_t;

    enum class contact_property_t {ADDRESS, EMAIL, ICON, NAME, TEL};

}


struct contact_picker::detail::physical_address_t
{
    ext::string country;
    ext::vector<ext::string> address_line;
    ext::string region;
    ext::string city;
    ext::string dependent_locality;
    ext::string postal_code;
    ext::string sorting_code;
    ext::string organization;
    ext::string recipient;
    ext::string phone_number;
};


struct contact_picker::detail::user_contact_t
{
    ext::vector<ext::string> names;
    ext::vector<ext::string> emails;
    ext::vector<ext::string> numbers;
    ext::vector<ext::string> addresses;
    ext::vector<std::unique_ptr<file_api::blob>> icons;
};


struct contact_picker::detail::contact_source_t
{
    ext::vector<std::unique_ptr<user_contact_t>> available_contacts;
    ext::vector<contact_property_t> supported_properties;
};
