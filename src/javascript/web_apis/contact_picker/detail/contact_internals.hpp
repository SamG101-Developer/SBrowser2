#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DETAIL_CONTACT_INTERNALS_CONTACT_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DETAIL_CONTACT_INTERNALS_CONTACT_INTERNALS_HPP

#include "ext/optional.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(contact_picker)

namespace file_api {class blob;}


namespace contact_picker::detail
{
    auto launch(
            ext::boolean allow_multiple,
            ext::vector_view<ext::string> properties)
            -> ext::optional<user_contact_t>;
};


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
    ext::vector<user_contact_t*> available_contacts;
    ext::vector<contact_property_t> supported_properties;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DETAIL_CONTACT_INTERNALS_CONTACT_INTERNALS_HPP
