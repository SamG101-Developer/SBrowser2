#pragma once
#ifndef SBROWSER2_VIOLATION_INTERNALS_HPP
#define SBROWSER2_VIOLATION_INTERNALS_HPP


#include "ext/memory.ixx"

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
            std::unique_ptr<policy_t> policy,
            ext::string_view directive)
            -> std::unique_ptr<violation_t>;

    auto create_violation_object(
            const fetch::detail::request_t& request,
            std::unique_ptr<policy_t> policy)
            -> std::unique_ptr<violation_t>;

    auto does_request_violate_policy(
            const fetch::detail::request_t& request,
            policy_t& csp)
            -> ext::boolean;
}


struct webappsec::detail::violation_t
{
    auto url() -> url::detail::url_t&;

    v8::Local<v8::Object> global_object;
    std::unique_ptr<url::detail::url_t> referrer;
    std::unique_ptr<url::detail::url_t> source_file;
    std::unique_ptr<policy_t> policy;
    std::observer_ptr<dom::nodes::element> element;
    ext::variant<violation_resource_t, std::unique_ptr<url::detail::url_t>> resource;
    ext::string effective_directive;
    ext::string sample;
    disposition_t disposition;
    ext::number<int> status;
    ext::number<uint> line_number;
    ext::number<uint> column_number;
};


#endif //SBROWSER2_VIOLATION_INTERNALS_HPP
