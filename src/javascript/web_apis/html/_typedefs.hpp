#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/pair.hpp"
#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/number.hpp"
#include "ext/queue.hpp"
#include "ext/string.hpp"
#include "ext/tuple.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(fetch)

namespace file_api {class blob;}
namespace file_api {class file;}
namespace html::elements {class html_element;}
namespace html::elements {class html_canvas_element;}
namespace html::elements {class html_image_element;}
namespace html::elements {class html_option_element;}
namespace html::elements {class html_opt_group_element;}
namespace html::elements {class html_video_element;}
namespace html::canvasing {class image_bitmap;}
namespace html::canvasing {class offscreen_canvas;}
namespace html::canvasing {class canvas_rendering_context_2d;}
namespace html::canvasing {class image_bitmap_rendering_context;}
namespace web_codecs::video {class video_frame;}
namespace mediacapture::main {class media_stream;}
namespace media::source {class media_source;}
namespace svg::elements {class svg_image_element;}
namespace webgl2::contexts {class webgl_rendering_context;}
namespace webgl2::contexts {class webgl2_rendering_context;}


namespace html::detail
{
    enum class history_handling_behaviour_t {DEFAULT, /* TODO */};
    enum class directionality_t {LTR, RTL, AUTO};
    enum class bidirectional_char_t: char32_t {L = 0x200e, R = 0x200f, AL = 0x061c, EN, ES, ET, AN, CS, NSM, BN, B, S, WS, ON, LRE, LRO, RLE, PDF, LRI, RLI, FSI, PDI};
    enum class state_t {UNAVAILABLE, PARTIALLY_AVAILABLE, COMPLETELY_AVAILABLE, BROKEN};
    enum class phase_t {PRE_MEDIA, MEDIA};
    enum class embedder_policy_value_t {UNSAFE_NONE, REQUIRE_CORP, CREDENTIALLESS};
    enum class cross_origin_opener_policy_value_t{UNSAFE_NONE, SAME_ORIGIN_ALLOW_POPUPS, SAME_ORIGIN, SAME_ORIGIN_PLUS_COEP};
    enum class lazy_loading_t {EAGER, LAZY};
    enum class rel_t {ALTERNATE, DNS_PREFETCH, ICON, MANIFEST, MODULE_PRELOAD, NEXT, PINGBACK, PRECONNECT, PREFETCH, PRELOAD, PRERENDER, SEARCH, STYLESHEET, CANONICAL};
    enum class http_equiv_t {CONTENT_LANGUAGE, CONTENT_TYPE, DEFAULT_STYLE, REFRESH, SET_COOKIE, X_UA_COMPATIBLE, CONTENT_SECURITY_POLICY};
    enum class can_play_type_result_t {MAYBE, PROBABLY};
    enum class text_track_mode_t {DISABLED, HIDDEN, SHOWING};
    enum class text_track_kind_t {SUBTITLES, CAPTIONS, DESCRIPTIONS, CHAPTERS, METADATA};
    enum class media_playback_direction_t {FORWARDS, BACKWARDS};
    enum class track_readiness_state_t {NOT_LOADED, LOADING, LOADED, FAILED_TO_LOAD};
    enum class track_mode_t {DISABLED, HIDDEN, SHOWING};
    enum class area_shape_t {CIRCLE, DEFAULT, POLYGON, RECTANGLE};
    enum class table_cell_scope_t {ROW, COL, ROWGROUP, COLGROUP, AUTO};
    enum class button_state_t {SUBMIT, RESET, BUTTON};
    enum class wrap_type_t {SOFT, HARD};
    enum class selection_mode_t {SELECT, START, END, PRESERVE};
    enum class canvas_context_mode_t {NONE, PLACEHOLDER, _2D, BITMAP_RENDERER, WEBGL, WEBGL2, WEBGPU};
    enum class predefined_color_space_t {SRGB, DISPLAY_P3};
    enum class canvas_fill_rule_t {NONZERO, EVENODD};
    enum class image_smoothing_quality {LOW, MEDIUM, HIGH};

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
    struct validity_state_t;
    struct command_facet_t;
    struct script_t;

    using name_value_group_t = ext::pair<ext::vector<elements::html_element*>, ext::vector<elements::html_element*>>;
    using name_value_groups_t = ext::vector<name_value_group_t>;
    using response_available_function_t = ext::function<void(fetch::detail::response_t*)>;
    using tuple_origin_t = ext::tuple<ext::string, ext::string, ext::number<short>, ext::string>;
    using origin_t = ext::variant<ext::string, tuple_origin_t>;
    using task_t = ext::function<void()>;
    using task_queue_t = ext::queue<task_t>;
    using media_provider_t = ext::variant<mediacapture::main::media_stream*, media::source::media_source*, file_api::blob*>;
    using option_like_element_t = ext::variant<elements::html_option_element*, elements::html_opt_group_element*>;
    using entry_t = ext::tuple<ext::string, ext::variant<ext::string, file_api::file*>>;
    using entry_list_t = ext::vector<entry_t>;
    using assigned_node_options_t = ext::map<ext::string, ext::any>;
    using rendering_context_t = ext::variant<
            html::canvasing::canvas_rendering_context_2d*,
            html::canvasing::image_bitmap_rendering_context,
            webgl2::contexts::webgl_rendering_context,
            webgl2::contexts::webgl2_rendering_context>;
    using blob_callback_t = ext::function<void(file_api::blob*)>;
    using html_or_svg_image_element_t = ext::variant<elements::html_image_element*, svg::elements::svg_image_element*>;
    using canvas_image_source_t = ext::variant<
            html_or_svg_image_element_t,
            elements::html_video_element*,
            elements::html_canvas_element*,
            canvasing::image_bitmap*,
            canvasing::offscreen_canvas*,
            web_codecs::video::video_frame*>;
    using canvas_rendering_context_2d_settings = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP
