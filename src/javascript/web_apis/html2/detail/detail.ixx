module;
#include "ext/macros.hpp"
#include <tl/expected.hpp>
#include <tl/optional.hpp>


export module apis.html.detail;

import apis.dom.types;
import apis.encoding.types;
import apis.fetch.types;
import apis.html.types;
import apis.url.types;
import ext.core;


// Make a class serializable by defining 2 methods -- one to serialize the class into a map and one to deserialize a
// class from a map into this class.
#define MAKE_SERIALIZABLE                                                                           \
    auto _serialize(ext::map<ext::string, ext::any>& serialized, ext::boolean for_storage) -> void; \
    auto _deserialize(const ext::map<ext::string, ext::any>& serialized, ext::boolean for_storage) -> this_t*;


// A transferable class is a class that inherits the EventTarget interface (so implicitly has no copy constructor or
// assignment), but has copy steps defined specially.
#define MAKE_TRANSFERABLE(t) \
    t(t&& other);            \
    auto operator=(t&& other) -> decltype(auto);


DEFINE_FWD_DECL_NAMESPACE_DETAIL(html)
{
    // [2.1.1] - Parallelism
    auto enqueue_steps(parallel_queue_t& queue, auto&& steps) -> void;
    auto start_new_parallel_queue() -> parallel_queue_t;

    // [2.1.4] - DOM Trees
    auto insertion_steps(dom::node* node) -> void;
    auto removing_steps(dom::node* node, dom::node* old_parent) -> void;
    auto node_inserted_into_document(dom::node* node) -> ext::boolean;
    auto node_removed_into_document(dom::node* node) -> ext::boolean;
    auto node_connected(dom::node* node) -> ext::boolean;
    auto node_disconnected(dom::node* node) -> ext::boolean;
    auto node_browsing_context_connected(dom::node* node) -> ext::boolean;
    auto node_browsing_context_disconnected(dom::node* node) -> ext::boolean;

    // [2.1.9] - Dependencies
    auto parse_css_color_value(ext::string_view color, dom::element* element) -> auto; // TODO

    // [2.3.4] - Numbers
    auto is_valid_integer(ext::string_view input) -> ext::boolean;
    auto parse_integer(ext::string_view input) -> ext::expected<ext::number>;

    auto is_valid_non_negative_integer(ext::string_view input) -> ext::boolean;
    auto parse_non_negative_integer(ext::string_view input) -> ext::expected<ext::number>;

    auto is_valid_floating_point_number(ext::string_view input) -> ext::boolean;
    auto best_representation_of_number_n_as_floating_point_number(ext::number string) -> ext::string;
    auto parse_floating_point_number(ext::string_view input) -> ext::expected<ext::number>;

    auto parse_dimension_values(ext::string_view input) -> ext::expected<ext::number>;
    auto current_dimension_value(ext::string_view value, ext::string_view input, ext::string_view::iterator position) -> ext::number;
    auto parse_non_zero_dimension_values(ext::string_view input) -> ext::expected<ext::number>;

    auto is_valid_list_of_floating_point_numbers(ext::string_view string) -> ext::boolean;
    auto parse_list_of_floating_point_numbers(ext::string_view string) -> ext::expected<ext::vector<ext::number>>;

    auto parse_list_of_dimensions(ext::string_view string) -> ext::expected<ext::vector<ext::number>>;

    auto number_days_in_month(ext::number<int> month) -> ext::number<int>;
    auto is_valid_month_string(ext::string_view input) -> ext::boolean;
    auto parse_month_string(ext::string_view input) -> ext::expected<ext::pair<year_t, month_t>>;
    auto parse_month_component(ext::string_view input, month_t::iterator position) -> ext::expected<ext::pair<year_t, month_t>>;

    auto is_valid_date_string(ext::string_view input) -> ext::boolean;
    auto parse_date_string(ext::string_view input) -> ext::expected<date_t>;
    auto parse_date_component(ext::string_view input, date_t::iterator position) -> ext::expected<date_t>;

    auto is_valid_yearless_date_string(ext::string_view input) -> ext::boolean;
    auto parse_yearless_string(ext::string_view input) -> ext::expected<ext::pair<month_t, day_t>>;
    auto parse_yearless_component(ext::string_view input, yearless_date_t::iterator position) -> ext::expected<ext::pair<month_t, day_t>>;

    auto is_valid_time_string(ext::string_view input) -> ext::boolean;
    auto parse_time_string(ext::string_view input) -> ext::expected<time_t>;
    auto parse_time_string_component(ext::string_view input, time_t::iterator position) -> ext::expected<time_t>;

    auto is_valid_local_date_and_time_string(ext::string_view input) -> ext::boolean;
    auto is_valid_normalized_local_date_and_time_string(ext::string_view input) -> ext::boolean;
    auto parse_local_date_and_time_string(ext::string_view input) -> ext::expected<ext::pair<date_t, time_t>>;

    auto is_valid_time_zone_offset_string(ext::string_view input) -> ext::boolean;
    auto parse_time_zone_offset_string(ext::string_view input) -> ext::expected<time_zone_offset_t>;
    auto parse_time_zone_offset_component(ext::string_view input, time_zone_offset_t::iterator position) -> ext::expected<time_zone_offset_t>;

    auto is_valid_global_date_and_time_string(ext::string_view input) -> ext::boolean;
    auto parse_global_date_and_time_string(ext::string_view input) -> ext::expected<ext::pair<time_t, time_zone_t>>;

    auto is_valid_week_string(ext::string_view input) -> ext::boolean;
    auto parse_week_string(ext::string_view input) -> ext::expected<ext::number<int>, ext::number<int>>;

    auto is_valid_duration_string(ext::string_view input) -> ext::boolean;
    auto is_duration_time_component(ext::string_view input) -> ext::boolean;
    auto parse_duration_string(ext::string_view input) -> ext::expected<duration_t>;

    auto is_valid_date_string_with_optional_time(ext::string_view input) -> ext::boolean;
    auto parse_date_or_time_string(ext::string_view input) -> ext::expected<ext::string>;

    auto is_valid_simple_color(ext::string_view input) -> ext::boolean;
    auto is_valid_lowercase_simple_color(ext::string_view input) -> ext::boolean;
    auto parse_simple_color(ext::string_view input) -> simple_colour_t;

    // [2.3.7] - Space-Separated Tokens
    auto is_unordered_set_of_unique_space_separated_tokens(ext::view_of_t<space_separated_tokens_t> input) -> ext::boolean;
    auto is_ordered_set_of_unique_space_separated_tokens(ext::view_of_t<space_separated_tokens_t> input) -> ext::boolean;

    // [2.3.9] - References
    auto is_valid_hash_name_reference(ext::string_view input) -> ext::boolean;
    auto parse_hash_name_reference(ext::string_view input, dom::node* scope) -> dom::node*;

    // [2.3.10] - Media Queries
    auto is_valid_media_query(ext::string_view input) -> ext::boolean;
    auto matches_environment(ext::string_view input) -> ext::boolean;

    // [2.3.11] - Unique Internal Values
    auto create_unique_internal_value() -> unique_internal_value_t;

    // [2.4] - URLs (TODO : 2.4.3)
    auto is_valid_non_empty_url(ext::string_view url) -> ext::boolean;
    auto is_valid_url_potentially_surrounded_by_spaces(ext::string_view url) -> ext::boolean;
    auto is_valid_non_empty_url_potentially_surrounded_by_spaces(ext::string_view url) -> ext::boolean;
    auto fallback_base_url(dom::document* document) -> const url::detail::url_t&;
    auto document_base_url(dom::document* document) -> const url::detail::url_t&;
    auto parse_url(ext::string_view url, dom::document* document) -> ext::expected<ext::pair<ext::string, std::unique_ptr<url::detail::url_t>>>;

    // [2.5] - Fetching Resources
    auto is_response_cors_same_origin(const fetch::detail::response_t& response) -> ext::boolean;
    auto is_response_cors_cross_origin(const fetch::detail::response_t& response) -> ext::boolean;
    auto resonses_unsafe_response(const fetch::detail::response_t& response) -> fetch::detail::response&;
    auto create_potential_cors_request(url::detail::url_t& url, fetch::detail::request_destination_t destination, detail::cors_setting_attribute_t cors_attribute_state, ext::boolean same_origin_fallback_flag) -> std::unique_ptr<fetch::detail::request_t>;
    auto extract_character_coding_from_meta_element(ext::string_view string) -> ext::optional<std::unique_ptr<encoding::detail::encoding_t>>;

    // [2.5.6] - TODO

    // [2.5.7] - Lazy Loading Attributes TODO lazy load resumption steps
    auto will_lazy_load_element(dom::element* element) -> ext::boolean;
    auto start_intersection_observing_lazy_loading_element(dom::element* element) -> void;
    auto stop_intersection_observing_lazy_loading_element(dom::element* element) -> void;
    auto lazy_load_root_margin() -> ext::number<int>; // TODO : return type?

    // [2.5.8] - Blocking Attributes
    auto blocking_tokens_set(dom::element* element) -> ext::set<>; // TODO
    auto is_potentially_render_blocking(dom::element* element) -> ext::boolean;
    auto is_implicity_potentially_render_blocking(dom::element* element) -> ext::boolean;

    // [2.7] - Structured Data
    template <typename T> auto structured_serialize_internal(T&& value, ext::boolean for_storage, ext::map<ext::string, ext::any>&& memory) -> ext::map<ext::string, ext::any>;
    template <typename T> auto structured_serialize(T&& value) -> ext::map<ext::string, ext::any>;
    template <typename T> auto structured_serialize_for_storage(T&& value) -> ext::map<ext::string, ext::any>;
    template <typename T> auto structured_deserialize(T&& value, const js::env::env& env, ext::map<ext::string, ext::any>&& memory) -> ext::map<ext::string, ext::any>;
    template <typename T> auto structured_serialize_with_transfer(T&& value, ext::vector<>&& transfer_list) -> ext::map<ext::string, ext::any>;
    template <typename T> auto structured_deserialize_with_transfer(ext::map<ext::string, ext::any>&& serialize_with_transfer_result, const js::env::env& env) -> ext::map<ext::string, ext::any>;

    // [3.1.4] - Reporting Document Loading Status
    auto update_current_document_readiness(dom::document* document) -> void;
    auto has_active_parser(dom::document* document) -> ext::boolean;

    // [3.1.5] - Render Blocking Mechanism
    auto allows_adding_render_blocking_elements(dom::document* document) -> ext::boolean;
    auto is_render_blocked(dom::document* document) -> ext::boolean;
    auto is_render_blocking_element(dom::element* element) -> ext::boolean;
    auto block_rendering(dom::element* element) -> void;
    auto unblock_rendering(dom::element* element) -> void;

    // [3.2.5] - Content Models
    auto is_metadata_content(dom::node* node) -> ext::boolean;
    auto is_flow_content(dom::node* node) -> ext::boolean;
    auto is_sectioning_content(dom::node* node) -> ext::boolean;
    auto is_heading_content(dom::node* node) -> ext::boolean;
    auto is_phrasing_content(dom::node* node) -> ext::boolean;
    auto is_embedded_content(dom::node* node) -> ext::boolean;
    auto is_interactive_content(dom::node* node) -> ext::boolean;
    auto is_palpable_content(dom::node* node) -> ext::boolean;
    auto is_script_supporting_element(dom::node* node) -> ext::boolean;

    // [3.2.6] - Global Attributes
    auto advisory_information(dom::node* node) -> ext::string;
    auto language_of_node(dom::node* node) -> ext::string;
    auto directionality(dom::node* node) -> directionality_t;
    auto directionality(dom::attr* attr) -> directionality_t;

    // [3.2.7] - Inner & Outer Text
    auto rendered_text_collection_steps(dom::node* node) -> ext::vector<ext::string>;
    auto rendered_text_fragment(ext::string&& input, dom::document* document) -> std::unique_ptr<dom::document_fragment>;
    auto merge_with_next_text_node(dom::text* text) -> void;

    // [4.2.3] - HtmlBaseElement
    template <linkable_element T> auto get_elements_target(T* element) -> ext::string;
    auto set_frozen_base_url(element* element) -> void;

    // [4.2.4] - HtmlLinkElement
    auto default_fetch_and_process_linked_resource(html::html_link_element* element) -> void;
    auto create_link_request(const link_processing_options_t& options) -> std::unique_ptr<fetch::detail::request_t>;
    auto create_link_options(html::html_link_element* element) -> std::unique_ptr<link_processing_options_t>;
    auto extract_links_from_headers(ext::view_of_t<fetch::detail::headers_t> headers) -> ext::vector<std::unique_ptr<html::html_link_element>>;
    auto process_link_headers(dom::document* document, const fetch::detail::response_t& response, phase_t phase) -> void;
    auto apply_link_options_from_parsed_header_attributes(link_processing_options_t& options, ext::map<ext::string, ext::any>&& attributes) -> void;

    auto process_early_hint_headers(const fetch::detail::response_t& response, js::env::env& reserved_environment) -> void;

    // [4.2.6] - HtmlStyleElement
    auto update_style_block(html::html_style_element* element) -> void;
    auto obtain_style_sheet_critical_subresources(html::html_style_element* element) -> void;

    // [4.2.7] - Interactions of Styling & Scripting
    auto contributes_script_blocking_style_sheet(dom::element* element, dom::document* document) -> ext::boolean;
    auto has_style_sheet_blocking_scripts(dom::document* document) -> ext::boolean;
    auto has_no_style_sheet_blocking_scripts(dom::document* document) -> ext::boolean;

    // [4.3.10] - Address Element
    auto contact_information(dom::node* node) -> ext::string;

    // [4.3.11] - Headings & Outlines
    auto outline(dom::document* document) -> ext::span<html::html_heading_element*>;

    // [4.4.5] - HtmlOListElement
    auto starting_value(html::html_olist_element* element) -> ext::number<long>;

    // [4.4.8] - HtmlUListElement
    auto list_owner(html::html_element* element) -> html_element*; // TODO : signature
    auto ordinal_value(html::html_element* element) -> ext::number<long>;

    // [4.4.9] - HtmlDListElement
    auto name_value_groups(html::html_dlist_element* element) -> ext::span<ext::pair<ext::span<html_element*>, ext::span<html_element*>>>;
    auto process_dt_or_dd_for_node(dom::node* node) -> void;

    // [4.4.14] - Main Element
    auto hierarchically_correct_main_element(html::html_element* element) -> ext::boolean;
}
