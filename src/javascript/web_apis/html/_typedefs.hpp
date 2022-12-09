#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP






#include "ext/optional.ixx"

#include "ext/set.hpp"

#include "ext/tuple.ixx"


#include "ext/vector.hpp"
#include <QtGui/QTransform>
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(url)

namespace file_api {class blob;}
namespace file_api {class file;}
namespace html::elements {class html_element;}
namespace html::elements {class html_canvas_element;}
namespace html::elements {class html_image_element;}
namespace html::elements {class html_option_element;}
namespace html::elements {class html_opt_group_element;}
namespace html::elements {class html_video_element;}
namespace html::canvasing {class image_bitmap;}
namespace html::canvasing {class image_data;}
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


#define MAKE_SERIALIZABLE \
    auto _serialize(ext::map<ext::string, ext::any>& serialized, ext::boolean for_storage) -> void; \
    auto _deserialize(ext::map<ext::string, ext::any>& serialized, ext::boolean for_storage) -> self_t*;

#define MAKE_TRANSFERABLE(t) \
    t(const t& other);       \
    auto operator=(const t& other) -> decltype(auto);


namespace html::detail
{
    enum class history_handling_behaviour_t {DEFAULT, /* TODO */};
    enum class directionality_t {LTR, RTL, AUTO, _};
    enum class bidirectional_char_t: char32_t {L = 0x200e, R = 0x200f, AL = 0x061c, EN, ES, ET, AN, CS, NSM, BN, B, S, WS, ON, LRE, LRO, RLE, PDF, LRI, RLI, FSI, PDI};
    enum class state_t {UNAVAILABLE, PARTIALLY_AVAILABLE, COMPLETELY_AVAILABLE, BROKEN};
    enum class phase_t {PRE_MEDIA, MEDIA};
    enum class embedder_policy_value_t {UNSAFE_NONE, REQUIRE_CORP, CREDENTIALLESS};
    enum class cross_origin_opener_policy_value_t {UNSAFE_NONE, SAME_ORIGIN_ALLOW_POPUPS, SAME_ORIGIN, SAME_ORIGIN_PLUS_COEP};
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
    enum class media_data_processing_t {CANNOT_BE_FETCHED, CAN_BE_FETCHED_UNSUPPORTED_FORMAT, HAS_AUDIO_TRACK,
            HAS_VIDEO_TRACK, ENOUGH_FETCHED_TO_DETERMINE_DURATION, ENTIRE_FETCHED, CONNECTION_INTERUPPTED, CORRUPTED,
            ABORTED, PARTIAL_UNSUPPORTED_CODECS, DECLARES_MEDIA_RESOURCE_SPECIFIC_TEXT_TRACK};
    enum class media_error_type_t {MEDIA_ERR_ABORTED = 1, MEDIA_ERR_NETWORK = 2, MEDIA_ERR_DECODE = 3, MEDIA_ERR_SRC_NOT_SUPPORTED = 4};
    enum class drop_effect_t {NONE, COPY, LINK, MOVE};
    enum class effect_allowed_t {NONE, COPY, COPY_LINK, COPY_MOVE, LINK, LINK_MOVE, MOVE, ALL, UNINITIALIZED};
    enum class drag_data_store_mode_t {READ_WRITE, READ_ONLY, PROTECTED};
    enum class drag_data_item_kind_t {TEXT, FILE, _};
    enum class editable_enter_key_hit_t {ENTER, DONE, GO, NEXT, PREVIOUS, SEARCH, SEND};
    enum class editable_input_mode_t {NONE, TEXT, TEL, URL, EMAIL, NUMERIC, DECIMAL, SEARCH};
    enum class image_orientation_t {NONE, FLIPY};
    enum class premultiply_alpha {NONE, PREMULITPLY, DEFAULT};
    enum class color_space_conversion {NONE, DEFAULT};
    enum class resize_quality {PIXELATED, LOW, MEDIUM, HIGH};
    enum class form_method_t {GET, POST, DIALOG};
    enum class form_enctype_t {/* TODO */};
    enum class image_decoding_hint_t {SYNC, ASYNC, AUTO};
    enum class lazy_loading_t {EAGER, LAZY};
    enum class cross_origin_settings_attribute_t {ANONYMOUS, USE_CREDENTIALS};
    enum class preload_t {NONE, METADATA, AUTO};
    enum class local_name_t {A, ABBR, ADDRESS, AREA, ARTICLE, ASIDE, AUDIO, B, BASE, BDI, BDO, BLOCKQUOTE, BODY, BR,
            BUTTON, CANVAS, CAPTION, CITE, CODE, COL, COLGROUP, DATA, DATALIST, DD, DEL, DETAILS, DFN, DIALOG, DIV, DL,
            DT, EM, EMBED, FIELDSET, FIGCAPTION, FIGURE, FOOTER, FORM, H1, H2, H3, H4, H5, H6, HEAD, HEADER, HGROUP, HR,
            HTML, I, IFRAME, IMG, INPUT, INS, KBD, LABEL, LEGEND, LI, LINK, MAIN, MAP, MARK, MATHML, MATH, MENU, META,
            METER, NAV, NOSCRIPT, OBJECT, OL, OPTGROUP, OPTION, OUTPUT, P, PICTURE, PRE, PROGRESS, Q, RP, RT, RUBY, S,
            SAMP, SCRIPT, SECTION, SELECT, SLOT, SMALL, SOURCE, SPAN, STRONG, STYLE, SUB, SUMMARY, SUP, SVG, TABLE,
            TBODY, TD, TEMPLATE, TEXTAREA, TFOOT, TH, THEAD, TIME, TITLE, TR, TRACK, U, UL, VAR, VIDEO, WBR
    };
    enum class blocking_t {RENDER};
    enum class track_element_kind_t {SUBTITLES, CAPTIONS, DESCRIPTIONS, CHAPTERS, METADATA};
    enum class document_readiness_state_t {COMPLETE, INTERACTIVE};
    enum class scroll_restoration_t {AUTO, MANUAL};
    enum worjer_global_scope_type_t {CLASSIC, MODULE};

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
    struct task_queue_t;
    struct drag_data_store_item_list_t;
    struct drag_data_store_t;
    struct navigable_t;
    struct session_history_t;
    struct origin_t;

    using name_value_group_t = ext::pair<ext::vector<elements::html_element*>, ext::vector<elements::html_element*>>;
    using name_value_groups_t = ext::vector<name_value_group_t>;
    using response_available_function_t = ext::function<void(fetch::detail::response_t*)>;
    using task_t = ext::function<void()>;
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
    using browsing_context_set_t = ext::set<browsing_context_t*>;
    using property_descriptor_t = ext::string; // TODO
    using cross_origin_property_descriptor_map_t = ext::map<ext::tuple<v8::Object, v8::Object, ext::string>, property_descriptor_t>; // TODO
    using tuple_origin_t = ext::tuple<ext::string, ext::string, ext::number<short>, url::detail::domain_t>; // SCHEME, HOST, ...
    using scheme_and_host_t = ext::tuple<ext::string, ext::string>;
    using site_t = ext::variant<origin_t, scheme_and_host_t>; // TODO
    using structured_serialize_options_t = ext::map<ext::string, ext::any>;
    using timer_handler_t = ext::variant<ext::string, ext::function<void()>>;
    using image_bitmap_source_t = ext::extend_variant_t<canvas_image_source_t, file_api::blob*, canvasing::image_data*>;
    using image_bitmap_options_t = ext::map<ext::string, ext::any>;
    using worklet_options_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML__TYPEDEFS_HPP
