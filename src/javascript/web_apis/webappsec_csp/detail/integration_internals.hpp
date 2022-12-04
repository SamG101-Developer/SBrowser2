#pragma once
#ifndef SBROWSER2_INTEGRATION_INTERNALS_HPP
#define SBROWSER2_INTEGRATION_INTERNALS_HPP


#include "ext/vector.hpp"
#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(webappsec)
#include INCLUDE_INNER_TYPES(webappsec_csp)
namespace dom::nodes {class node;}
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}


namespace webappsec::detail
{
    auto report_content_security_policy_violations(
            const fetch::detail::request_t& request)
            -> void;

    auto should_request_be_blocked_by_content_security_policy(
            const fetch::detail::request_t& request)
            -> should_t;

    auto should_response_to_request_be_blocked_by_content_security_policy(
            const fetch::detail::response_t& response,
            const fetch::detail::request_t& request)
            -> should_t;
    
    auto run_content_security_policy_initialization(
            dom::nodes::document* document)
            -> void;

    auto run_content_security_policy_initialization(
            v8::Local<v8::Object> global_object)
            -> void;

    auto retrieve_content_security_policy_list(
            dom::nodes::node* object)
            -> ext::vector<policy_t*>;

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
            ext::vector<policy_t>& csp_list,
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

    // TODO : Integrations with HTML
}


#endif //SBROWSER2_INTEGRATION_INTERNALS_HPP
