#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DETAIL_CONTACT_INTERNALS_CONTACT_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DETAIL_CONTACT_INTERNALS_CONTACT_INTERNALS_HPP

#include "ext/optional.ixx"

#include "ext/vector.hpp"
#include "ext/span.hpp"
#include INCLUDE_INNER_TYPES(contact_picker)

namespace file_api {class blob;}


namespace contact_picker::detail
{
    auto launch(
            ext::boolean allow_multiple,
            ext::vector_span<ext::string> properties)
            -> ext::optional<user_contact_t>;
}


struct contact_picker::detail::user_contact_t
{
    ext::vector<ext::string> names;
    ext::vector<ext::string> emails;
    ext::vector<ext::string> numbers;
    ext::vector<ext::string> addresses;
    ext::vector<std::unique_ptr<file_api::blob>> icons;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DETAIL_CONTACT_INTERNALS_CONTACT_INTERNALS_HPP
