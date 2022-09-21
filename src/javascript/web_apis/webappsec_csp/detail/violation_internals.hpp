#pragma once
#ifndef SBROWSER2_VIOLATION_INTERNALS_HPP
#define SBROWSER2_VIOLATION_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include <v8-local-handle.h>
#include <v8-object.h>
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(url)
#include INCLUDE_INNER_TYPES(webappsec_csp)

namespace dom::nodes {class element;}


namespace webappsec::detail
{
    auto create_violation_object(
            v8::Local<v8::Object> global_object,
            content_security_policy_t& csp,
            ext::string_view directive)
            -> violation_t;

    auto create_violation_object(
            const fetch::detail::request_t& request,
            content_security_policy_t& csp)
            -> violation_t;

    auto does_request_violate_policy(
            const fetch::detail::request_t& request,
            content_security_policy_t& csp)
            -> ext::boolean;
}


#endif //SBROWSER2_VIOLATION_INTERNALS_HPP
