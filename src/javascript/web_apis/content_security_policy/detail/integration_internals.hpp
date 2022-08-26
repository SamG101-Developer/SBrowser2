#pragma once
#ifndef SBROWSER2_INTEGRATION_INTERNALS_HPP
#define SBROWSER2_INTEGRATION_INTERNALS_HPP

#include "ext/string.hpp"
#include "ext/vector.hpp"
#include <v8-forward.h>
#include USE_INNER_TYPES(content_security_policy)
#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(html)
namespace dom::nodes {class node;}
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}


namespace content_security_policy::detail
{
    auto report_content_security_policy_violations(
            const fetch::detail::request_t& request)
            -> void;

    auto should_request_be_blocked_by_content_security_policy(
            const fetch::detail::request_t& request)
            -> ext::boolean;

    auto should_response_be_blocked_by_content_security_policy(
            const fetch::detail::response_t& response,
            const fetch::detail::request_t& request)
            -> ext::boolean;
    
    auto run_content_security_policy_initialization(
            dom::nodes::document* document)
            -> void;

    auto run_content_security_policy_initialization(
            v8::Local<v8::Object> global_object)
            -> void;

    auto retrieve_content_security_policy_list(
            dom::nodes::node* object)
            -> ext::vector<content_security_policy_t*>;

    auto should_elements_inline_type_behaviour_be_blocked_by_content_security_policy(
            dom::nodes::element* element,
            ext::string_view type)
            -> ext::string;

    auto should_navigation_request_of_type_be_blocked_by_content_security_policy(
            fetch::detail::request_t& request,
            ext::string_view type)
            -> ext::string;

    auto should_navigation_response_to_navigation_request_of_type_in_target_be_blocked_by_content_security_policy(
            const fetch::detail::request_t& request,
            const fetch::detail::response_t& response,
            ext::vector<content_security_policy_t>& csp_list,
            ext::string_view type,
            const html::detail::browsing_context_t& target)
            -> ext::string;

    auto should_rtc_connection_be_blocked(
            v8::Local<v8::Object> global_object)
            -> ext::string;

    auto ensure_content_security_policy_does_not_block_string_compilation(
            v8::Local<v8::Context> realm,
            ext::string source)
            -> void;

    auto ensure_content_security_policy_does_not_block_was_byte_compilation(
            v8::Local<v8::Context> realm)
            -> void;
}


#endif //SBROWSER2_INTEGRATION_INTERNALS_HPP
