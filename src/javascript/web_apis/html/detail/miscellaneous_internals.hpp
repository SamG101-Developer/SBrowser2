#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_MISCELLANEOUS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_MISCELLANEOUS_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"

#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(url)

namespace html::detail
{
    auto create_potential_cors_request(
            url::detail::url_t& url,
            fetch::detail::destination_t destination,
            fetch::detail::mode_t cors_attribute_state,
            ext::boolean&& same_origin_fallback_flag = false)
            -> fetch::detail::request_t;

    auto parse_url(
            const ext::string& url_string,
            const dom::nodes::document* document)
            -> ext::pair<ext::string, url::detail::url_t>;

    auto serialize_url(
            const url::detail::url_t& url_record)
            -> ext::string;

    auto matches_about_blank(
            const url::detail::url_t& url_record)
            -> ext::boolean;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_MISCELLANEOUS_INTERNALS_HPP
