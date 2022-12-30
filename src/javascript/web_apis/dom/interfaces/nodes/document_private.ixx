module;
#include "ext/macros.hpp"
#include <tuplet/tuple.hpp>


export module apis.dom.document:p;
import apis.dom.node;
import apis.dom.mixins.document_or_element_node;
import apis.dom.mixins.document_or_shadow_root;
import apis.dom.mixins.non_element_parent_node;

IMPORT_ALL_TYPES(dom);
IMPORT_ALL_TYPES(webappsec_permissions_policy);


DEFINE_PRIVATE_CLASS(dom, document)
        : dom::node_private
        , dom::document_or_element_node_private
        , dom::document_or_shadow_root_private
        , dom::non_element_parent_node_private
        , dom::parentable_node_private
        // , dom::xpath::xpath_evaluator_base_private
{
public:
    MAKE_QIMPL(document);
    document_private();

public:
    /* [DOM] */
    auto is_document_available_to_user(ext::string_view) -> ext::boolean;
    auto is_document_fully_active() -> ext::boolean;
    auto has_active_parser() const -> ext::boolean;
    auto document_has_style_sheets_blocking_scripts() const -> ext::boolean;
    auto convert_nodes_into_node(ext::type_is<node*, ext::string> auto&&... nodes) const -> node*;
    auto adopt(node* node) -> node*;
    auto document_element() const -> element*;

    std::unique_ptr<encoding::encoding> encoding;
    std::unique_ptr<url::detail::url_t> url;
    ext::string content_type;
    ext::string type = u"xml";
    ext::string mode = u"no-quirks";
    std::shared_ptr<html::detail::origin_t> origin;
    dom::dom_implementation* implementation;

    /* [HTML] */
    // Policies & Permissions
    std::unique_ptr<html::detail::policy_container_t> policy_container;
    std::unique_ptr<html::detail::cross_origin_opener_policy_value_t> cross_origin_opener_policy;
    std::unique_ptr<permissions_policy::detail::internal_permissions_policy_t> permissions_policy;

    detail::module_map_t module_map;
    ext::boolean is_initial = false;
    ext::string referrer;
    std::unique_ptr<html::other::history> history;

    // Document Timing & Context
    std::unique_ptr<html::detail::document_load_timing_info_t> load_timing_info;
    std::unique_ptr<html::detail::document_unload_timing_info_t> unload_timing_info;
    std::unique_ptr<html::detail::browsing_context_t> browsing_context;

    ext::set<element*> render_blocking_elements;
    ext::boolean will_declaratively_refresh;
    ext::number<int> script_blocking_style_sheet_counter = 0;
    ext::map<html::detail::preload_key_t*, html::detail::preload_entry_t*> preloaded_resources;
    std::unique_ptr<intersection_observer::intersection_observer> lazy_load_intersection_observer;
    ext::map<html::detail::available_image_t*, std::byte[]> list_of_available_images;
    ext::boolean design_mode_enabled;
    html::detail::sandboxing_flag_set_t active_sandboxing_set;
    html::detail::document_readiness_state_t current_readiness_state;

    // IFrame
    ext::boolean iframe_load_in_progress_flag;
    ext::boolean mute_iframe_flag;

    // Scripts
    html::elements::html_script_element* pending_paring_blocking_script;
    ext::set<html::elements::html_script_element*> set_of_scripts_to_execute;
    ext::vector<html::elements::html_script_element*> list_of_scripts_to_execute_in_order;
    ext::vector<html::elements::html_script_element*> list_of_scripts_to_execute_in_order_when_document_finished_parsing;

    // Elements
    auto title_element() const -> html::elements::html_title_element* {};
    auto head_element() const -> html::elements::html_head_element* {};
    auto body_element() const -> html::elements::html_body_element* {};
    auto html_element() const -> html::elements::html_html_element* {};
    html::detail::html_or_svg_image_element_t current_script;

    // Other
    html::detail::directionality_t dir;
    std::unique_ptr<range> active_range;

    /* [DEVICE_POSTURE] */
    ext::number<double> current_posture;

    /* [FULLSCREEN] */
    ext::vector<ext::tuple<ext::string, element*>> list_of_pending_fullscreen_events;
    std::observer_ptr<element> fullscreen_element;

    /* [PAINT_TIMING] */
    ext::set<ext::string> previously_reported_paints;

    /* [Largest-Contentful-Paint] */
    ext::number<int> largest_contentful_paint_size = 0;
    ext::set<ext::tuple<dom::element*, fetch::request*>> content_set; // TODO: std::weak-ptr<T> ?

    /* [WebAppSec-Permissions-Policy] */
    std::unique_ptr<webappsec_permissions_policy::permissions_policy>;

    /* [CSS_ANIMATION_WORKLET] */
    ext::map<ext::string, css::detail::document_animator_definition_t*> document_animator_definitions;

    /* [CSS_LAYOUT] */
    ext::map<ext::string, css::detail::document_layout_definition_t*> document_layout_definitions;

    /* [INTERSECTION_OBSERVERS] */
    ext::boolean intersection_observer_task_queued;

    /* [CSS_WEB_ANIMATIONS] */
    std::unique_ptr<css::detail::document_timeline_t> default_timeline;

    /* [SCREEN-WAKE-LOCK] */
    ext::map<screen_wake_lock::detail::wake_lock_type, ext::vector<screen_wake_lock::wake_lock_sentinel*>> acive_locks;
};
