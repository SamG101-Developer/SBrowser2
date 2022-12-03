#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTENT_SECURITY_POLICY__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTENT_SECURITY_POLICY__TYPEDEFS_HPP

#include "ext/number.ixx"

#include "ext/string.hpp"
#include "ext/vector.hpp"
#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(url)
namespace dom::nodes {class element;}


namespace webappsec::detail
{
    struct policy_t;
    struct violation_t;
    struct directive_value_t;

    enum class disposition_t {ENFORCE, REPORT};
    enum class source_t {HEADER, META};
    enum class violation_resource_t {INLINE, EVAL, WASM_EVAL};
    enum class security_policy_violation_event_disposition_t {ENFORCE, REPORT};

    using directive_t = ext::pair<ext::string, std::unique_ptr<directive_value_t>>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTENT_SECURITY_POLICY__TYPEDEFS_HPP
