module;
#include "ext/macros.hpp"


export module apis.mimesniff.detail;
import apis.mimesniff.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(mimesniff)
{
    // [3] - Terminology
    template <ext::char_like T> auto is_http_token_code_point(T code_point) -> ext::boolean;
    template <ext::char_like T> auto is_http_quoted_string_token_code_point(T code_point) -> ext::boolean;
    template <ext::char_like T> auto is_binary_byte(T byte) -> ext::boolean;
    template <ext::char_like T> auto is_whitespace_byte(T byte) -> ext::boolean;
    template <ext::char_like T> auto is_tag_terminating_byte(T byte) -> ext::boolean;

    // [4] - MIME type miscellaneous
    /* [4.2] */ auto essence(const mime_type_t& mime_type) -> ext::string;
                auto mime_type_supported_by_user_agent(const mime_type_t& mime_type) -> ext::boolean;
    /* [4.3] */ auto is_valid_mime_type(ext::string_view string) -> ext::boolean;
                auto is_valid_mime_type_no_parameters(ext::string_view string) -> ext::boolean;
    /* [4.4] */ auto parse_mime_type(ext::string input) -> ext::expected<mime_type_t>;
                auto parse_mime_type_from_bytes(ext::u8string input) -> ext::expected<std::unique_ptr<mime_type_t>>;
    /* [4.5] */ auto serialize_mime_type(const mime_type_t& mime_type) -> ext::string;
                auto serialize_mime_type_to_bytes(const mime_type_t& mime_type) -> ext::u8string;
    /* [4.6] */ auto is_image_mime_type(const mime_type_t& mime_type) -> ext::boolean;
                auto is_audio_or_video_mime_type(const mime_type_t& mime_type) -> ext::boolean;
                auto is_font_mime_type(const mime_type_t& mime_type) -> ext::boolean;
                auto is_zip_based_mime_type(const mime_type_t& mime_type) -> ext::boolean;
                auto is_archive_mime_type(const mime_type_t& mime_type)-> ext::boolean;
                auto is_xml_mime_type(const mime_type_t& mime_type) -> ext::boolean;
                auto is_html_mime_type(const mime_type_t& mime_type) -> ext::boolean;
                auto is_scriptable_mime_type(const mime_type_t& mime_type)-> ext::boolean;
                auto is_javascript_mime_type(const mime_type_t& mime_type) -> ext::boolean;
                auto is_json_mime_type(const mime_type_t& mime_type) -> ext::boolean;

    // [5] - Handing Resources
    /* [5.1] */ auto determine_supplied_mime_type_of_resource(const resource_t& resource) -> std::unique_ptr<mime_type_t>;
    /* [5.2] */ auto read_resource_header(const resource_t& resource) -> resource_header_t;

    // [6]
    /* [6.0] */ auto pattern_matching_algorithm(byte_t* input, byte_pattern_t pattern, pattern_mask_t mask, ext::set<byte_t>&& ignore) -> ext::boolean;
    /* [6.1] */ auto determine_matching_image_mime_type(byte_t* sequence) -> std::unique_ptr<mime_type_t>;
    /* [6.2] */ auto determine_matching_audio_or_video_matching_algorithm(byte_t* sequence) -> std::unique_ptr<mime_type_t>;
    /* [6.3] */ auto determine_matching_font_mime_type(byte_t* sequence) -> mime_type_t;
    /* [6.4] */ auto determine_matching_archive_mime_type(byte_t* sequence) -> mime_type_t;

    auto matches_mp4_signature(byte_t* sequence) -> ext::boolean;
    auto matches_webm_signature(byte_t* sequence) -> ext::boolean;
    auto matches_mp3_header_signature(byte_t* sequence) -> ext::boolean;
    auto matches_mp3_no_id3_signature(byte_t* sequence) -> ext::boolean;
    auto compute_mp3_frame_size() -> ext::number<size_t>;
    auto parse_mp3_frame() -> void;
    auto parse_vint(byte_t* sequence, ext::number<size_t> length, ext::number<size_t> iter) -> std::tuple<ext::number<int>, ext::number<int>>;
    auto matching_padded_sequence(/* TODO */);

    // [7]
    /* [7.0] */ auto mime_type_sniffing(const resource_t& resource) -> std::unique_ptr<mime_type_t>;
    /* [7.1] */ auto identify_unknown_mime_type(const resource_t& resource) -> std::unique_ptr<mime_type_t>;
    /* [7.2] */ auto distinguish_if_resource_is_text_or_binary(const resource_t& resource) -> std::unique_ptr<mime_type_t>;
    /* [7.3] */ auto distinguish_if_resource_is_feed_or_html(const resource_t& resource) -> std::unique_ptr<mime_type_t>;

    // [8] - Context specific sniffing
    /* [8.2] */ auto sniff_images_specifically(const resource_t& resource) -> void;
    /* [8.3] */ auto sniff_audio_or_video_specifically(const resource_t& resource) -> void;
    /* [8.4] */ auto sniff_in_plugin_context(const resource_t& resource) -> void;
    /* [8.5] */ auto sniff_in_style_context(const resource_t& resource) -> void;
    /* [8.6] */ auto sniff_in_script_context(const resource_t& resource) -> void;
    /* [8.7] */ auto sniff_in_font_context(const resource_t& resource) -> void;
    /* [8.8] */ auto sniff_in_text_track_context(const resource_t& resource) -> void;
    /* [8.9] */ auto sniff_in_cache_manifest_context(const resource_t& resource) -> void;
}
