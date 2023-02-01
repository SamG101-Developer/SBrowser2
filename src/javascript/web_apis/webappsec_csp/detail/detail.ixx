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
    auto pre_request_check(fetch_directive_t directive, const fetch::detail::request_t& request, const policy_t& csp) -> should_t;
    auto post_request_check(fetch_directive_t directive, const fetch::detail::request_t& request, const fetch::detail::response_t& response, const policy_t& csp) -> should_t;
    auto inline_check(fetch_directive_t directive, dom::element* element, ext::string_view type, ext::string_view source, const policy_t& csp) -> should_t;
    auto initialization(fetch_directive_t directive, dom::document* document, const policy_t& csp) -> should_t;
    auto pre_navigation_check(fetch_directive_t directive, const fetch::detail::request_t& request, ext::string_view navigation_type, const policy_t& csp) -> should_t;
    auto navigation_response_check(fetch_directive_t directive, const fetch::detail::request_t& request, ext::string_view navigation_type, const fetch::detail::response_t& response, const html::detail::browsing_context_t& browsing_context, ext::string_view type, const policy_t& csp) -> should_t;
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

    // [5] - Reporting
    /* [5.2] */ auto obtain_blocked_uri_of_violations_resource(ext::string_view violation_resource) -> ext::string;
    /* [5.3] */ auto obtain_serialization_of_violation(const violation_t& violation) -> ext::string;
    /* [5.4] */ auto strip_url_for_violation_report(url::detail::url_t& url) -> ext::string;
    /* [5.5] */ auto report_violation(const violation_t& violation) -> void;

    // [6.7] - Matching
    /* [6.7.2.01] */ auto does_request_violate_policy(const fetch::detail::request_t& request, const policy_t& policy) -> const directive_t&;
    /* [6.7.2.02] */ auto does_resource_hint_violate_policy(const fetch::detail::request_t& request, const policy_t& policy) -> const directive_t&;
    /* [6.7.2.03] */ auto does_nonce_match_source_list(ext::string_view nonce, ext::view_of_t<source_list_t> source_list) -> ext::boolean;
    /* [6.7.2.04] */ auto does_request_match_source_list(fetch::request& request, ext::view_of_t<source_list_t> source_list, const policy_t& csp) -> ext::boolean;
    /* [6.7.2.05] */ auto does_response_to_request_match_source_list(const fetch::request& request, ext::view_of_t<source_list_t> source_list, const policy_t& csp) -> ext::boolean;
    /* [6.7.2.06] */ auto does_url_match_source_list_in_origin_with_redirected_count(const url::detail::url_t& url, ext::view_of_t<source_list_t> source_list, ext::string_view origin, ext::number<int> redirect_count) -> ext::boolean;
    /* [6.7.2.07] */ auto does_url_match_expression_in_origin_with_redirected_count(const url::detail::url_t& url, ext::string_view expression, ext::string_view origin, ext::number<int> redirect_count) -> ext::boolean;
    /* [6.7.2.08] */ auto scheme_part_matches(ext::string_view a, ext::string_view b) -> ext::boolean;
    /* [6.7.2.09] */ auto host_part_matches(ext::string_view a, ext::string_view b) -> ext::boolean;
    /* [6.7.2.10] */ auto port_part_matches(ext::string_view a, ext::string_view b) -> ext::boolean;
    /* [6.7.2.11] */ auto path_part_matches(ext::string_view a, ext::string_view b) -> ext::boolean;

    /* [6.7.3.1] */ auto is_element_nonceable(dom::element* element) -> ext::string;
    /* [6.7.3.2] */ auto does_source_list_allow_all_inline_behaviour_for_type(ext::view_of_t<source_list_t> source_list, ext::string_view type) -> ext::string;
    /* [6.7.3.3] */ auto does_element_match_source_list_for_type_and_source(dom::nodes::element* element, ext::view_of_t<source_list_t> source_list, ext::string_view type, ext::string_view source) -> ext::string;

    /* [6.8.1] */ auto effective_directive_for_request(const fetch::detail::request_t& request) -> ext::string;
    /* [6.8.2] */ auto get_effective_directive_inline_checks(ext::string_view type) -> ext::string;
    /* [6.8.3] */ auto get_fetch_directive_fallback_list(ext::string_view directive_name) -> ext::span<ext::string>;
    /* [6.8.4] */ auto should_fetch_directive_execute(ext::string_view effective_directive_name, ext::string_view directive_name, const policy_t& csp) -> ext::boolean;
}
