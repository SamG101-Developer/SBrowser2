#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_MISCELLANEOUS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_MISCELLANEOUS_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "url/url.hpp"
namespace fetch::detail::request_internals {class internal_request;}
namespace fetch::detail::request_internals {enum class destination_t;}
namespace fetch::detail::request_internals {enum class mode_t;}

namespace html::detail::miscellaneous_internals
{
    auto create_potential_cors_request(
            url::url_object& url,
            fetch::detail::request_internals::destination_t destination,
            fetch::detail::request_internals::mode_t cors_attribute_state,
            ext::boolean&& same_origin_fallback_flag = false)
            -> fetch::detail::request_internals::internal_request;

    auto parse_url(
            const ext::string& url_string,
            const dom::nodes::document* document)
            -> ext::pair<ext::string, url::url_object>;

    auto serialize_url(
            const url::url_object& url_record)
            -> ext::string;

    auto matches_about_blank(
            const url::url_object& url_record)
            -> ext::boolean;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_MISCELLANEOUS_INTERNALS_HPP
