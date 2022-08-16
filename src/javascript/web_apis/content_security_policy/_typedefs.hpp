#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTENT_SECURITY_POLICY__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTENT_SECURITY_POLICY__TYPEDEFS_HPP

#include "ext/number.hpp"
#include "ext/pair.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include "url/url.hpp"
#include <v8-forward.h>

namespace content_security_policy::detail
{
    struct content_security_policy_t;
    struct violation_t;
    enum class disposition_t {ENFORCE, REPORT};
    enum class source_t {HEADER, META};
    using directive_t = ext::pair<ext::string, ext::vector<ext::string>>;
}


struct content_security_policy::detail::content_security_policy_t
{
    ext::vector<directive_t> directive_set;
    disposition_t disposition;
    source_t source;
    ext::string self_origin;
};


struct content_security_policy::detail::violation_t
{
    v8::Local<v8::Object> global_object;
    url::url_object url;
    ext::number<int> status;
    ext::string resource;
    ext::string referrer;
    const content_security_policy_t& csp;
    disposition_t disposition;
    ext::string effective_directive;
    url::url_object source_file;
    ext::number<int> line_number;
    ext::number<int> column_number;
    dom::nodes::element* element;
    ext::string sample;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONTENT_SECURITY_POLICY__TYPEDEFS_HPP
