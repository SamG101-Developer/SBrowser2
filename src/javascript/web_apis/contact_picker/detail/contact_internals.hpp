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




#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DETAIL_CONTACT_INTERNALS_CONTACT_INTERNALS_HPP
