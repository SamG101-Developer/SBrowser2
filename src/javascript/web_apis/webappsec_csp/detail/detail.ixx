module;
#include "ext/macros.hpp"


export module apis.webappsec_csp.detail;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(webappsec_csp)
{
    // [2.2] - Policies
    auto parse_serialized_csp(ext::string_view string, source_t source, disposition_t disposition) -> std::unique_ptr<policy_t>;
    auto parse_csp_list(ext::string_view string, source_t source, disposition_t disposition) -> ext::vector<std::unique_ptr<policy_t>>;
    auto parse_responses_csp(const fetch::detail::response_t& response) -> ext::vector<std::unique_ptr<policy_t>>;

    // [2.3] - Directives
    auto pre_request_check(const directive_t& directive, const fetch::detail::request_t& request, const policy_t& csp) -> should_t;
    auto post_request_check(const directive_t& directive, const fetch::detail::request_t& request, const fetch::detail::response_t& response, const policy_t& csp) -> should_t;
    auto inline_check(const directive_t& directive, dom::element* element, ext::string_view type, ext::string_view source, const policy_t& csp) -> should_t;
    auto initialization(const directive_t& directive, dom::document* document, const policy_t& csp) -> should_t;
    auto pre_navigation_check(const directive_t& directive, const fetch::detail::request_t& request, ext::string_view navigation_type, const policy_t& csp) -> should_t;
    auto navigation_response_check(const directive_t& directive, const fetch::detail::request_t& request, ext::string_view navigation_type, const fetch::detail::response_t& response, const html::detail::browsing_context_t& browsing_context, ext::string_view type, const policy_t& csp) -> should_t;
    auto webrtc_pre_connect_check(const policy_t& csp) -> should_t;

    // [2.4] - Violations
    auto create_violation_object(v8::Local<v8::Object> global_object, std::unique_ptr<policy_t> policy, ext::string_view directive) -> std::unique_ptr<violation_t>;
    auto create_violation_object(const fetch::detail::request_t& request, std::unique_ptr<policy_t> policy) -> std::unique_ptr<violation_t>;

    // [4.1] - Integration with Fetch
    /* [4.1.1] */ auto report_content_security_policy_violations(const fetch::detail::request_t& request) -> void;
    /* [4.1.2] */ auto should_request_be_blocked_by_content_security_policy(const fetch::detail::request_t& request) -> should_t;
    /* [4.1.3] */ auto should_response_to_request_be_blocked_by_content_security_policy(const fetch::detail::response_t& response, const fetch::detail::request_t& request) -> should_t;

    // [4.2] - Integration with Html TODO - other function modifications
    /* [4.2.1] */ auto run_content_security_policy_initialization(dom::document* document) -> void;
    /* [4.2.2] */ auto retrieve_content_security_policy_list(dom::node* object) -> ext::vector<policy_t*>;
    /* [4.2.3] */ auto should_elements_inline_type_behaviour_be_blocked_by_content_security_policy(dom::nodes::element* element, ext::string_view type) -> ext::string;
    /* [4.2.4] */ auto should_navigation_request_of_type_be_blocked_by_content_security_policy(fetch::detail::request_t& request, ext::string_view type) -> ext::string;
    /* [4.2.5] */ auto should_navigation_response_to_navigation_request_of_type_in_target_be_blocked_by_content_security_policy(const fetch::detail::request_t& request, const fetch::detail::response_t& response, ext::vector<policy_t>& csp_list, ext::string_view type, const html::detail::browsing_context_t& target) -> ext::string;
    /* [4.2.6] */ auto run_content_security_policy_initialization(v8::Local<v8::Object> global_object) -> void;

    // [4.3] - Integration with WebRTC
    /* [4.3.1] */ auto should_rtc_connection_be_blocked(v8::Local<v8::Object> global_object)-> ext::string;

    // [4.4] - Integration with ECMAScript
    /* [4.4.1] */ auto ensure_content_security_policy_does_not_block_string_compilation(v8::Local<v8::Context> realm, ext::string source) -> void;

    // [4.5] - Integration with WebAssembly
    /* [4.5.1] */ auto ensure_content_security_policy_does_not_block_was_byte_compilation(v8::Local<v8::Context> realm) -> void;
}
