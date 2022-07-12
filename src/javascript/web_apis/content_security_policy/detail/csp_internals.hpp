#pragma once
#ifndef SBROWSER2_CSP_INTERNALS_HPP
#define SBROWSER2_CSP_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include "url/url.hpp"
namespace dom::nodes {class document;}

namespace content_security_policy::detail::csp_internals
{
    struct content_security_policy;
    enum disposition_t {ENFORCE, REPORT};
    enum source_t {HEADER, META};
    using directive_t = std::pair<ext::string, ext::string_vector>;

    auto contains_header_delivered_csp(
            ext::vector<content_security_policy*>& csp_list)
            -> ext::boolean;

    auto serialize_csp(
            content_security_policy& csp_policy)
            -> ext::string;

    auto serialize_csp_list(
            ext::vector<content_security_policy*> csp_list)
            -> ext::string;

    auto parse_csp(
            ext::string_view string,
            ext::string_view source,
            ext::string_view disposition)
            -> content_security_policy;

    auto parse_csp_list(
            ext::string_view string,
            ext::string_view source,
            ext::string_view disposition)
            -> ext::vector<content_security_policy*>;

    auto parse_responses_csp(
            ext::string_view response)
            -> content_security_policy;

    auto is_base_allowed_for_document(
            url::url_object& base,
            dom::nodes::document* document)
            -> ext::string;
}


struct content_security_policy::detail::csp_internals::content_security_policy
{
    ext::vector<directive_t> directive_set;
    disposition_t disposition;
    source_t source;
    ext::string self_origin;
};


#endif //SBROWSER2_CSP_INTERNALS_HPP
