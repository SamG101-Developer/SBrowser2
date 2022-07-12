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
namespace dom::nodes {class element;}
namespace fetch::detail::request_internals {struct internal_request;}
namespace fetch::detail::response_internals {struct internal_response;}
namespace content_security_policy::detail::csp_internals {enum disposition_t;}
namespace content_security_policy::detail::csp_internals {struct content_security_policy;}

namespace content_security_policy::detail::violation_internals
{
    struct violation;

    auto create_violation_object(
            v8::Local<v8::Object> global_object,
            csp_internals::content_security_policy& csp,
            ext::string_view directive)
            -> violation;

    auto create_violation_object(
            fetch::detail::request_internals::internal_request& internal_request_object,
            csp_internals::content_security_policy& csp)
            -> violation;

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
            csp_internals::content_security_policy& csp)
            -> ext::boolean;
}


struct content_security_policy::detail::violation_internals::violation
{
    v8::Local<v8::Object> global_object;
    url::url_object url;
    ext::number<int> status;
    ext::string resource;
    ext::string referrer;
    csp_internals::content_security_policy& csp;
    csp_internals::disposition_t disposition;
    ext::string effective_directive;
    url::url_object source_file;
    ext::number<int> line_number;
    ext::number<int> column_number;
    dom::nodes::element* element;
    ext::string sample;
};


#endif //SBROWSER2_VIOLATION_INTERNALS_HPP
