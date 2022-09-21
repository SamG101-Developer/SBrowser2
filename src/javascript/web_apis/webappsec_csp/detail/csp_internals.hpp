#pragma once
#ifndef SBROWSER2_CSP_INTERNALS_HPP
#define SBROWSER2_CSP_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/pair.hpp"
#include "ext/set.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include INCLUDE_INNER_TYPES(webappsec_csp)
#include INCLUDE_INNER_TYPES(url)

namespace dom::nodes {class document;}


namespace webappsec::detail
{
    auto contains_header_delivered_csp(
            ext::vector<content_security_policy_t*>& csp_list)
            -> ext::boolean;

    auto strongest_metadata(
            ext::set<ext::string>& metadata_list)
            -> ext::string_view;

    auto bytes_match_metadata_list(
            ext::string bytes,
            ext::set<ext::string>& metadata_list)
            -> ext::boolean;

    auto serialize_csp(
            content_security_policy_t& csp_policy)
            -> ext::string;

    auto serialize_csp_list(
            ext::vector<content_security_policy_t*> csp_list)
            -> ext::string;

    auto parse_metadata(
            ext::string_view metadata)
            -> ext::set<ext::string>;

    auto parse_csp(
            ext::string_view string,
            ext::string_view source,
            ext::string_view disposition)
            -> content_security_policy_t;

    auto parse_csp_list(
            ext::string_view string,
            ext::string_view source,
            ext::string_view disposition)
            -> ext::vector<content_security_policy_t*>;

    auto parse_responses_csp(
            ext::string_view response)
            -> content_security_policy_t;

    auto is_base_allowed_for_document(
            url::detail::url_t& base,
            dom::nodes::document* document)
            -> ext::string;
}


#endif //SBROWSER2_CSP_INTERNALS_HPP
