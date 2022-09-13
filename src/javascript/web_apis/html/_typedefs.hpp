#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/pair.hpp"
#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/number.hpp"
#include "ext/queue.hpp"
#include "ext/set.hpp"
#include "ext/string.hpp"
#include "ext/tuple.hpp"
#include "ext/type_traits.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"
#include <QtGui/QTransform>
#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(url)

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
namespace webgpu {class gpu_canvas_context;}


namespace html::detail
{
    enum class history_handling_behaviour_t {DEFAULT, /* TODO */};
    enum class directionality_t {LTR, RTL, AUTO};
    enum class bidirectional_char_t: char32_t {L = 0x200e, R = 0x200f, AL = 0x061c, EN, ES, ET, AN, CS, NSM, BN, B, S, WS, ON, LRE, LRO, RLE, PDF, LRI, RLI, FSI, PDI};
    enum class state_t {UNAVAILABLE, PARTIALLY_AVAILABLE, COMPLETELY_AVAILABLE, BROKEN};
    enum class phase_t {PRE_MEDIA, MEDIA};
    enum class embedder_policy_value_t {UNSAFE_NONE, REQUIRE_CORP, CREDENTIALLESS};
    enum class cross_origin_opener_policy_value_t {UNSAFE_NONE, SAME_ORIGIN_ALLOW_POPUPS, SAME_ORIGIN, SAME_ORIGIN_PLUS_COEP};
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
    enum class canvas_fill_rule_t {EVENODD, NONZERO};
    enum class image_smoothing_quality_t {LOW, MEDIUM, HIGH};
    enum class canvas_line_cap_t {BUTT, ROUND, SQUARE};
    enum class canvas_line_join_t {ROUND, BEVEL, MITER};
    enum class canvas_text_align_t {START, END, LEFT, RIGHT, CENTER};
    enum class canvas_text_baseline_t {TOP, HANDING, MIDDLE, ALPHABETIC, IDEOGRAPHIC, BOTTOM};
    enum class canvas_direction_t {LTR, RTL, INHERIT};
    enum class canvas_font_kerning_t {AUTO, NORMAL, NONE};
    enum class canvas_font_stretch_t {ULTRA_CONDENSED, EXTRA_CONDENSED, CONDENSED, SEMI_CONDENSED, NORMAL, SEMI_EXPANDED, EXPANDED, EXTRA_EXPANDED, ULTRA_EXPANDED};
    enum class canvas_font_variant_caps_t {NORMAL, SMALL_CAPS, ALL_SMALL_CAPS, PETITE_CAPS, ALL_PETITE_CAPS, UNICASE, TITLING_CAPS};
    enum class canvas_text_rendering_t {AUTO, OPTIMIZE_SPEED, OPTIMIZE_LEGIBILITY, GEOMETRIC_PRECISIION};
    enum class bitmap_mode_t {BLANK, VALID};
    enum class offscreen_rendering_context_id_t {_2D, BITMAPRENDERER, WEBGL, WEBGL2, WEBGPU};
    enum class autocapitalize_hint_t {DEFAULT, NONE, SENTENCES, WORDS, CHARACTERS};
    enum class cross_origin_isolation_mode_t {NONE, LOGICAL, CONCRETE};
    enum class sandboxing_flag_set_t : long {NAVIGATION = 0x01, AUXILIARY_NAVIGATION = 0x02,
            TOP_LEVEL_NAVIGATION_WITHOUT_USER_ACTIVATION = 0x04, TOP_LEVEL_NAVIGATION_WITH_USER_ACTIVATION = 0x08,
            PLUGINS = 0x10, ORIGIN = 0x20, FORMS = 0x40, POINTER_LOCK = 0x80, SCRIPTS = 0x100,
            AUTOMATIC_FEATURES = 0x200, DOCUMENT_DOMAIN = 0x400, PROPAGATES_TO_AUXILIARY = 0x800, MODALS = 0x1000,
            ORIENTATION = 0x2000, PRESENTATION = 0x4000, DOWNLOADS = 0x8000, CUSTOM_PROTOCOLS = 0x16000};

    struct browsing_context_t;
    struct document_load_timing_info_t;
    struct document_unload_timing_info_t;
    struct available_image_t;
    struct image_request_t;
    struct image_bitmap_t;
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
    struct color_t;
    struct browsing_context_group_t;
    struct drawing_state_t;

    using name_value_group_t = ext::pair<ext::vector<elements::html_element*>, ext::vector<elements::html_element*>>;
    using name_value_groups_t = ext::vector<name_value_group_t>;
    using response_available_function_t = ext::function<void(fetch::detail::response_t*)>;
    using task_t = ext::function<void()>;
    using task_queue_t = ext::queue<task_t>;
    using media_provider_t = ext::variant<mediacapture::main::media_stream*, media::source::media_source*, file_api::blob*>;
    using option_like_element_t = ext::variant<elements::html_option_element*, elements::html_opt_group_element*>;
    using entry_t = ext::tuple<ext::string, ext::variant<ext::string, file_api::file*>>;
    using entry_list_t = ext::vector<entry_t>;
    using assigned_node_options_t = ext::map<ext::string, ext::any>;
    using rendering_context_t = ext::variant<
            html::canvasing::canvas_rendering_context_2d*,
            html::canvasing::image_bitmap_rendering_context*,
            webgl2::contexts::webgl_rendering_context*,
            webgl2::contexts::webgl2_rendering_context*>;
    using offscreen_rendering_context_t = ext::extend_variant_t<rendering_context_t, webgpu::gpu_canvas_context>;
    using blob_callback_param_t = ext::variant<canvasing::image_bitmap, file_api::file, file_api::blob, ext::variant_monostate_t>;
    using blob_callback_t = ext::function<void(blob_callback_param_t)>;
    using html_or_svg_image_element_t = ext::variant<elements::html_image_element*, svg::elements::svg_image_element*>;
    using canvas_image_source_t = ext::extend_variant_t<
            html_or_svg_image_element_t,
            elements::html_video_element*,
            elements::html_canvas_element*,
            canvasing::image_bitmap*,
            canvasing::offscreen_canvas*,
            web_codecs::video::video_frame*>;
    using canvas_rendering_context_2d_settings_t = ext::map<ext::string, ext::any>;
    using image_data_settings_t = ext::map<ext::string, ext::any>;
    using transform_t = QTransform;
    using image_bitmap_rendering_settings_t = ext::map<ext::string, ext::any>;
    using image_encode_options_t = ext::map<ext::string, ext::any>;
    using element_definition_options_t = ext::map<ext::string, ext::any>;
    using custom_element_constructor_t = ext::function<elements::html_element*()>;
    using validity_state_flags_t = ext::map<ext::string, ext::boolean>;
    using focus_options_t = ext::map<ext::string, ext::boolean>;
    using function_string_callback_t = ext::function<void(ext::string&& data)>;
    using browsing_context_set_t = ext::set<browsing_context_t*>;
    using property_descriptor_t = ext::string; // TODO
    using cross_origin_property_descriptor_map_t = ext::map<ext::tuple<v8::Object, v8::Object, ext::string>, property_descriptor_t>; // TODO
    using tuple_origin_t = ext::tuple<ext::string, ext::string, ext::number<short>, url::detail::domain_t>;
    using opaque_origin_t = ext::string;
    using origin_t = ext::variant<opaque_origin_t, tuple_origin_t>;
    using scheme_and_host_t = ext::tuple<ext::string, ext::string>;
    using site_t = ext::variant<opaque_origin_t, scheme_and_host_t>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP
