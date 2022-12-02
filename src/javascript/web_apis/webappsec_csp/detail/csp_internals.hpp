#pragma once
#ifndef SBROWSER2_CSP_INTERNALS_HPP
#define SBROWSER2_CSP_INTERNALS_HPP

#include "ext/boolean.ixx"
#include "ext/pair.ixx"
#include "ext/set.hpp"
#include "ext/span.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(url)
#include INCLUDE_INNER_TYPES(webappsec_csp)
namespace dom::nodes {class document;}


namespace webappsec::detail
{
    auto contains_header_delivered_csp(
            ext::vector_span<policy_t*> csp_list)
            -> ext::boolean;

    auto strongest_metadata(
            ext::set<ext::string>& metadata_list)
            -> ext::string_view;

    auto bytes_match_metadata_list(
            ext::string bytes,
            ext::set<ext::string>& metadata_list)
            -> ext::boolean;

    auto serialize_csp(
            policy_t& csp_policy)
            -> ext::string;

    auto serialize_csp_list(
            ext::vector_span<policy_t*> csp_list)
            -> ext::string;

    auto serialize_directive_name(
            const directive_t& directive)
            -> ext::string;

    auto serialize_source_list()
            -> ext::string;

    auto parse_metadata(
            ext::string_view metadata)
            -> ext::set<ext::string>;

    auto parse_csp(
            ext::string_view string,
            source_t source,
            disposition_t disposition)
            -> std::unique_ptr<policy_t>;

    auto parse_csp_list(
            ext::string_view string,
            source_t source,
            disposition_t disposition)
            -> ext::vector<std::unique_ptr<policy_t>>;

    auto parse_responses_csp(
            const fetch::detail::response_t& response)
            -> ext::vector<std::unique_ptr<policy_t>>;

    auto is_base_allowed_for_document(
            url::detail::url_t& base,
            dom::nodes::document* document)
            -> ext::string;
}


struct webappsec::detail::policy_t
{
    ext::vector<directive_t> directive_set;
    disposition_t disposition;
    source_t source;
    std::shared_ptr<html::detail::origin_t> self_origin;
};


#endif //SBROWSER2_CSP_INTERNALS_HPP
