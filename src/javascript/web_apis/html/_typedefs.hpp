#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP

#include "ext/pair.hpp"
#include "ext/functional.hpp"
#include "ext/number.hpp"
#include "ext/queue.hpp"
#include "ext/string.hpp"
#include "ext/tuple.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(fetch)

namespace file_api {class blob;}
namespace html::elements {class html_element;}
namespace html::elements {class html_option_element;}
namespace html::elements {class html_opt_group_element;}
namespace mediacapture::main {class media_stream;}
namespace media::source {class media_source;}


namespace html::detail
{
    enum class history_handling_behaviour_t {
        DEFAULT, /* TODO */};

    enum class directionality_t {
        LTR, RTL, AUTO};

    enum class bidirectional_char_t: char32_t {
        L = 0x200e, R = 0x200f, AL = 0x061c, EN, ES, ET, AN, CS, NSM, BN, B, S, WS, ON, LRE, LRO, RLE, PDF, LRI, RLI,
        FSI, PDI};

    enum class state_t {
        UNAVAILABLE, PARTIALLY_AVAILABLE, COMPLETELY_AVAILABLE, BROKEN};

    enum class phase_t {
        PRE_MEDIA, MEDIA};

    enum class embedder_policy_value_t {
        UNSAFE_NONE, REQUIRE_CORP, CREDENTIALLESS};

    enum class cross_origin_opener_policy_value_t{
        UNSAFE_NONE, SAME_ORIGIN_ALLOW_POPUPS, SAME_ORIGIN, SAME_ORIGIN_PLUS_COEP};

    enum class lazy_loading_t {
        EAGER, LAZY};

    enum class rel_t {
        ALTERNATE, DNS_PREFETCH, ICON, MANIFEST, MODULE_PRELOAD, NEXT, PINGBACK, PRECONNECT, PREFETCH, PRELOAD,
        PRERENDER, SEARCH, STYLESHEET, CANONICAL};

    enum class http_equiv_t {
        CONTENT_LANGUAGE, CONTENT_TYPE, DEFAULT_STYLE, REFRESH, SET_COOKIE, X_UA_COMPATIBLE, CONTENT_SECURITY_POLICY};

    enum class can_play_type_result_t {
        MAYBE, PROBABLY};

    enum class text_track_mode_t {DISABLED, HIDDEN, SHOWING};
    enum class text_track_kind_t {SUBTITLES, CAPTIONS, DESCRIPTIONS, CHAPTERS, METADATA};
    enum class media_playback_direction_t {FORWARDS, BACKWARDS};
    enum class track_readiness_state_t {NOT_LOADED, LOADING, LOADED, FAILED_TO_LOAD};
    enum class track_mode_t {DISABLED, HIDDEN, SHOWING};
    enum class area_shape_t {CIRCLE, DEFAULT, POLYGON, RECTANGLE};
    enum class table_cell_scope_t {ROW, COL, ROWGROUP, COLGROUP, AUTO};
    enum class button_state_t {SUBMIT, RESET, BUTTON};

    struct browsing_context_t;
    struct document_load_timing_info_t;
    struct document_unload_timing_info_t;
    struct image_request_t;
    struct available_image_t;
    struct image_source_t;
    struct link_processing_options_t;
    struct preload_key_t;
    struct preload_entry_t;
    struct policy_container_t;
    struct embedder_policy_t;
    struct cross_origin_opener_policy_t;

    using name_value_group_t = ext::pair<ext::vector<elements::html_element*>, ext::vector<elements::html_element*>>;
    using name_value_groups_t = ext::vector<name_value_group_t>;
    using response_available_function_t = ext::function<void(fetch::detail::response_t*)>;
    using tuple_origin_t = ext::tuple<ext::string, ext::string, ext::number<short>, ext::string>;
    using origin_t = ext::variant<ext::string, tuple_origin_t>;
    using task_t = ext::function<void()>;
    using task_queue_t = ext::queue<task_t>;
    using media_provider_t = ext::variant<mediacapture::main::media_stream*, media::source::media_source*, file_api::blob*>;
    using option_like_element_t = ext::variant<elements::html_option_element*, elements::html_opt_group_element*>;

}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP
