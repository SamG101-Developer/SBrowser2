#pragma once
#ifndef SBROWSER2_VIOLATION_INTERNALS_HPP
#define SBROWSER2_VIOLATION_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include "url/url.hpp"

#include <v8-local-handle.h>
#include <v8-object.h>
#include USE_INNER_TYPES(content_security_policy)
namespace dom::nodes {class element;}
namespace fetch::detail::request_internals {struct internal_request;}
namespace fetch::detail::response_internals {struct internal_response;}

namespace content_security_policy::detail
{
    auto create_violation_object(
            v8::Local<v8::Object> global_object,
            content_security_policy_t& csp,
            ext::string_view directive)
            -> violation_t;

    auto create_violation_object(
            fetch::detail::request_internals::internal_request& internal_request_object,
            content_security_policy_t& csp)
            -> violation_t;

    auto report_content_security_policy_violations(
            fetch::detail::request_internals::internal_request& request)
            -> void;

    auto should_request_be_blocked_by_content_security_policy(
            fetch::detail::request_internals::internal_request& request)
            -> ext::boolean;

    auto should_response_be_blocked_by_content_security_policy(
            fetch::detail::response_internals::internal_response& response,
            fetch::detail::request_internals::internal_request& request)
            -> ext::boolean;

    auto does_request_violate_policy(
            fetch::detail::request_internals::internal_request& request,
            content_security_policy_t& csp)
            -> ext::boolean;
}


#endif //SBROWSER2_VIOLATION_INTERNALS_HPP
