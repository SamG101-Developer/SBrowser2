#pragma once
#ifndef SBROWSER2_MATCHING_INTERNALS_HPP
#define SBROWSER2_MATCHING_INTERNALS_HPP

#include "content_security_policy/_typedefs.hpp"
#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include "url/url.hpp"
namespace dom::nodes {class element;}
namespace fetch {class request;}

namespace content_security_policy::detail
{
    auto does_nonce_match_source_list(
            ext::string_view nonce,
            ext::vector_view<ext::string> source_list)
            -> ext::boolean;

    auto does_request_match_source_list(
            fetch::request& request,
            ext::vector_view<ext::string> source_list,
            content_security_policy_t& csp)
            -> ext::boolean;

    auto does_response_to_request_match_source_list(
            fetch::request& request,
            ext::vector_view<ext::string> source_list,
            content_security_policy_t& csp)
            -> ext::boolean;

    auto does_url_match_source_list_in_origin_with_redirected_count(
            url::url_object& url,
            ext::vector_view<ext::string> source_list,
            ext::string_view origin,
            ext::number<int> redirect_count)
            -> ext::boolean;

    auto does_url_match_expression_in_origin_with_redirected_count(
            url::url_object& url,
            ext::string_view expression,
            ext::string_view origin,
            ext::number<int> redirect_count)
            -> ext::boolean;

    auto scheme_part_matches(
            ext::string_view a,
            ext::string_view b)
            -> ext::boolean;

    auto host_part_matches(
            ext::string_view a,
            ext::string_view b)
            -> ext::boolean;

    auto port_part_matches(
            ext::string_view a,
            ext::string_view b)
            -> ext::boolean;

    auto path_part_matches(
            ext::string_view a,
            ext::string_view b)
            -> ext::boolean;

    auto is_element_nonceable(
            dom::nodes::element* element)
            -> ext::string;

    auto does_source_list_allow_all_inline_behaviour_for_type(
            ext::vector_view<ext::string> source_list,
            ext::string_view type)
            -> ext::string;

    auto does_element_match_source_list_for_type_and_source(
            dom::nodes::element* element,
            ext::vector_view<ext::string> source_list,
            ext::string_view type,
            ext::string_view source)
            -> ext::string;
}


#endif //SBROWSER2_MATCHING_INTERNALS_HPP
