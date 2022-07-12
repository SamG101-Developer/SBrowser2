#pragma once
#ifndef SBROWSER2_INTEGRATION_INTERNALS_HPP
#define SBROWSER2_INTEGRATION_INTERNALS_HPP


#include "ext/string.hpp"
#include "ext/vector.hpp"
#include <v8-object.h>
namespace content_security_policy::detail::csp_internals {struct content_security_policy;}
namespace dom::nodes {class node;}
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace fetch::detail::request_internals {struct internal_request;}
namespace fetch::detail::response_internals {struct internal_response;}
namespace html::detail::context_internals {struct browsing_context;}

namespace content_security_policy::detail::integration_internals
{
    auto run_content_security_policy_initialization(
            dom::nodes::document* document)
            -> void;

    auto run_content_security_policy_initialization(
            v8::Local<v8::Object> global_object)
            -> void;

    auto retrieve_content_security_policy_list(
            dom::nodes::node* object)
            -> ext::vector<csp_internals::content_security_policy*>;

    auto should_elements_inline_type_behaviour_be_blocked_by_content_security_policy(
            dom::nodes::element* element,
            ext::string_view type)
            -> ext::string;

    auto should_navigation_request_of_type_be_blocked_by_content_security_policy(
            fetch::detail::request_internals::internal_request& request,
            ext::string_view type)
            -> ext::string;

    auto should_navigation_response_to_navigation_request_of_type_in_target_be_blocked_by_content_security_policy(
            fetch::detail::request_internals::internal_request& request,
            fetch::detail::response_internals::internal_response& response,
            ext::vector<csp_internals::content_security_policy>& csp_list,
            ext::string_view type,
            html::detail::context_internals::browsing_context* target)
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
