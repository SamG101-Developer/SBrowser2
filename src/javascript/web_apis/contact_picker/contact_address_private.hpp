#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACT_ADDRESS_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACT_ADDRESS_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"


DEFINE_PRIVATE_CLASS(contact_picker, contact_address)
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


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTACT_PICKER_CONTACT_ADDRESS_PRIVATE_HPP
