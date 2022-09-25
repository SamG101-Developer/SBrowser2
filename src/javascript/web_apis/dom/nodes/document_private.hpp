#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_DOCUMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_DOCUMENT_PRIVATE_HPP

#include "dom/nodes/node_private.hpp"

#include "ext/pimpl.hpp"
#include "ext/string.hpp"

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(permissions_policy)
#include INCLUDE_INNER_TYPES(url)

namespace dom::nodes {class element;}
namespace encoding {class encoding;}
namespace html::elements {class html_script_element;}
namespace intersection_observer {class intersection_observer;}


DEFINE_PRIVATE_CLASS(dom::nodes, document)
        : node_private
        , mixins::document_or_element_node_private
        , mixins::document_or_shadow_root_private
        , mixins::non_element_parent_node_private
        , mixins::parentable_node_private
        , xpath::xpath_evaluator_base_private
{
    /* [DOM] */
    std::unique_ptr<encoding::encoding> encoding;
    std::unique_ptr<url::detail::url_t> url;
    ext::string content_type;
    ext::string type = "xml";
    ext::string mode = "no-quirks";
    html::detail::origin_t origin;
    dom::other::dom_implementation* implementation;

    /* [HTML] */
    // Policies & Permissions
    std::unique_ptr<html::detail::policy_container_t> policy_container;
    std::unique_ptr<html::detail::cross_origin_opener_policy_value_t> cross_origin_opener_policy;
    std::unique_ptr<permissions_policy::detail::internal_permissions_policy_t> permissions_policy;

    detail::module_map_t module_map;
    ext::boolean is_initial = false;

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

    // IFrame
    ext::boolean iframe_load_in_progress_flag;
    ext::boolean mute_iframe_flag;

    // Scripts
    html::elements::html_script_element* pending_paring_blocking_script;
    ext::set<html::elements::html_script_element*> set_of_scripts_to_execute;
    ext::vector<html::elements::html_script_element*> list_of_scripts_to_execute_in_order;
    ext::vector<html::elements::html_script_element*> list_of_scripts_to_execute_in_order_when_document_finished_parsing;

    /* [DEVICE_POSTURE] */
    ext::number<double> s_current_posture;

    /* [FULLSCREEN] */
    ext::vector<ext::tuple<ext::string, element*>> list_of_pending_fullscreen_events;

    /* [PAINT_TIMING] */
    ext::set<ext::string> previously_reported_paints;


    /* [CSS_ANIMATION_WORKLET] */
    ext::map<ext::string, css::detail::document_animator_definition_t*> document_animator_definitions;

    /* [CSS_LAYOUT] */
    ext::map<ext::string, css::detail::document_layout_definition_t*> document_layout_definitions;

    /* [INTERSECTION_OBSERVERS] */
    ext::boolean intersection_observer_task_queued;

    /* [CSS_WEB_ANIMATIONS] */
    std::unique_ptr<css::detail::document_timeline_t> default_timeline;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_DOCUMENT_PRIVATE_HPP