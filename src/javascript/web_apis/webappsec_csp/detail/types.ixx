module;
#include "ext/macros.hpp"


export module apis.webappsec_csp.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(webappsec_csp)
{
    // [2.2] - Policies
    struct policy_t;
    using serialized_csp_t = ext::string;

    // [2.3] - Directives
    struct directive_value_t;
    using directive_t = ext::pair<ext::string, std::unique_ptr<directive_value_t>>;
    using source_list_t = ext::set<ext::variant<ext::string, directive_t>>;
    using serialized_directive_t = ext::string;
    using serialized_source_list_t = ext::string;

    // [2.4] - Violations
    struct violation_t;

    // [6] - Directives
    enum class underlying_directive_t {
        CONNECT_SRC, DEFAULT_SRC, FONT_SRC, IMG_SRC, MANIFEST_SRC, MEDIA_SRC, OBJECT_SRC, SCRIPT_SRC, SCRIPT_SRC_ELEM,
        SCRIPT_SRC_ATTR, STYLE_SRC, STYLE_SRC_ELEM, STYLE_SRC_ATTR, WEB_RTC, WORKER_SRC, BASE_URI, SANDBOX, FORM_ACTION,
        FORM_ANCESTORS, REPORT_URI, REPORT_TO, SCRIPT};

    //
    enum class disposition_t {ENFORCE, REPORT};
    enum class source_t {HEADER, META};
    enum class violation_resource_t {INLINE, EVAL, WASM_EVAL};
    enum class security_policy_violation_event_disposition_t {ENFORCE, REPORT};
}


struct webappsec_csp::detail::policy_t
{
    ext::vector<directive_t> directive_set;
    disposition_t disposition;
    source_t source;
    std::shared_ptr<html::detail::origin_t> self_origin;
};


struct webappsec_csp::detail::directive_value_t
{
    source_list_t source_list;
};


struct webappsec::detail::violation_t
{
    auto url() -> url::detail::url_t&;

    v8::Local<v8::Object> global_object;
    ext::number<int> status;
    ext::variant<violation_resource_t, std::unique_ptr<url::detail::url_t>> resource;
    std::unique_ptr<url::detail::url_t> referrer;
    std::unique_ptr<policy_t> policy;
    disposition_t disposition;
    ext::string effective_directive;
    std::unique_ptr<url::detail::url_t> source_file;
    ext::number<uint> line_number;
    ext::number<uint> column_number;
    std::observer_ptr<dom::nodes::element> element;
    ext::string sample;
};
