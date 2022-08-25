#ifndef SBROWSER2_DOCUMENT_HPP
#define SBROWSER2_DOCUMENT_HPP

#include "dom/nodes/node.hpp"
#include "dom/mixins/document_or_element_node.hpp"
#include "dom/mixins/document_or_shadow_root.hpp"
#include "dom/mixins/non_element_parent_node.hpp"
#include "dom/mixins/parentable_node.hpp"
#include "dom/xpath/xpath_evaluator_base.hpp"
#include "ext/map_like.hpp"
namespace dom::nodes {class document;}

#include "ext/concepts.hpp"
#include "ext/map.hpp"
#include "ext/set.hpp"
#include "ext/tuple.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"
#include <range/v3/view/any_view.hpp>

#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(permissions_policy)
#include USE_INNER_TYPES(page_visibility)
#include USE_INNER_TYPES(url)

namespace dom::nodes {class attr;}
namespace dom::nodes {class cdata_section;}
namespace dom::nodes {class comment;}
namespace dom::nodes {class document_fragment;}
namespace dom::nodes {class document_type;}
namespace dom::nodes {class processing_instruction;}
namespace dom::nodes {class text;}
namespace dom::nodes {class window_proxy;}

namespace dom::node_ranges {class range;}
namespace dom::node_iterators {class node_filter;}
namespace dom::node_iterators {class node_iterator;}
namespace dom::node_iterators {class tree_walker;}
namespace dom::other {class dom_implementation;}

namespace html::detail::image_internals {struct available_image;}
namespace html::elements {class html_body_element;}
namespace html::elements {class html_head_element;}
namespace html::elements {class html_html_element;}
namespace html::elements {class html_image_element;}
namespace html::elements {class html_link_element;}
namespace html::elements {class html_form_element;}
namespace html::elements {class html_script_element;}
namespace html::elements {class html_title_element;}
namespace html::elements {class html_element;}
namespace html::other {class location;}

namespace intersection_observer {class intersection_observer;}
namespace permissions_policy {class permissions_policy_object;}
namespace svg::elements {class svg_script_element;}

namespace dom::detail {auto lookup_custom_element_definition(const nodes::document*, ext::string_view, ext::string_view, ext::string_view) -> custom_element_definition_t*;}


class dom::nodes::document
        : public node
        , public mixins::document_or_element_node
        , public mixins::document_or_shadow_root
        , public mixins::non_element_parent_node
        , public mixins::parentable_node
        , public xpath::xpath_evaluator_base
        , public ext::map_like<ext::string, ranges::any_view<element*>>
{
public aliases:
    using module_map_t = ext::map<
            ext::tuple<ext::string, url::detail::url_t>,
            ext::string>;

    using html_or_svg_script_element_t = ext::variant<
            std::unique_ptr<html::elements::html_script_element>,
            std::unique_ptr<svg::elements::svg_script_element>>;

public friends:
    friend struct mixins::document_or_element_node;

    friend auto dom::detail::lookup_custom_element_definition(
            const nodes::document* document, ext::string_view namespace_, ext::string_view local_name,
            ext::string_view is) -> detail::custom_element_definition_t*;

public constructors:
    document();

public js_methods:
    /* DOM */
    [[nodiscard]] auto create_element(ext::string&& local_name, ext::map<ext::string, ext::any>&& options = {}) const -> element;
    [[nodiscard]] auto create_element_ns(ext::string&& namespace_, ext::string&& qualified_name, ext::map<ext::string, ext::any>&& options = {}) const -> element;
    [[nodiscard]] auto create_document_fragment() const -> document_fragment;
    [[nodiscard]] auto create_text_node(ext::string&& data) const -> text;
    [[nodiscard]] auto create_cdata_section_node(ext::string&& data) const -> cdata_section;
    [[nodiscard]] auto create_comment(ext::string&& data) const -> comment;
    [[nodiscard]] auto create_processing_instruction(ext::string&& target, ext::string&& data) const -> processing_instruction;
    [[nodiscard]] auto create_attribute(ext::string&& local_name) const -> attr;
    [[nodiscard]] auto create_attribute_ns(ext::string&& namespace_, ext::string&& qualified_name) const -> attr;

    [[nodiscard]] auto create_range() const -> node_ranges::range;
    auto create_node_iterator(node* root, ulong what_to_show = 0xFFFFFFFF, node_iterators::node_filter* filter = nullptr) const -> node_iterators::node_iterator;
    auto create_tree_walker(node* root, ulong what_to_show = 0xFFFFFFFF, node_iterators::node_filter* filter = nullptr) const -> node_iterators::tree_walker;

    auto import_node(node* new_node, ext::boolean&& deep = false) -> node*;
    auto adopt_node(node* new_node) -> node*;

    /* HTML */
    auto open() -> document*;
    auto open(ext::string_view url, ext::string_view name, ext::string_view features) -> window_proxy*;
    auto close() -> void;
    auto write(type_is<ext::string> auto&&... text) -> void;
    auto write_ln(type_is<ext::string> auto&&... text) -> void;

    auto has_focus() -> ext::boolean;
    auto query_command_enabled(ext::string_view command_id) -> ext::boolean;
    auto query_command_indeterm(ext::string_view command_id) -> ext::boolean;
    auto query_command_state(ext::string_view command_id) -> ext::boolean;
    auto query_command_supported(ext::string_view command_id) -> ext::boolean;
    auto query_command_value(ext::string_view command_id) -> ext::boolean;

    /* POINTER_LOCK */
    auto exit_pointer_lock() -> void;

    /* FULLSCREEN */
    auto exit_fullscreen() -> std::promise<void>;

public js_properties:
    /* DOM */
    ext::property<url::detail::url_t> url;
    ext::property<ext::string> compat_mode;
    ext::property<ext::string> character_set;
    ext::property<ext::string> content_type;
    ext::property<document_type*> doctype;
    ext::property<std::unique_ptr<element>> document_element;
    ext::property<std::unique_ptr<other::dom_implementation>> implementation;

    /* HTML */
    ext::property<std::unique_ptr<html::other::location>> location;
    ext::property<ext::string> domain;
    ext::property<ext::string> referrer;
    ext::property<ext::string> cookie;
    ext::property<ext::string> last_modified;
    ext::property<ext::string> ready_state;
    ext::property<ext::string> title; // TODO : CE_REACTIONS
    ext::property<ext::string> dir; // TODO : CE_REACTIONS

    ext::property<std::unique_ptr<html::elements::html_body_element>> body; // TODO : CE_REACTIONS
    ext::property<std::unique_ptr<html::elements::html_head_element>> head; // TODO : CE_REACTIONS
    ext::property<ranges::any_view<html::elements::html_image_element*>> images;
    ext::property<ranges::any_view<html::elements::html_link_element*>> links;
    ext::property<ranges::any_view<html::elements::html_form_element*>> forms;
    ext::property<ranges::any_view<html::elements::html_script_element*>> scripts;
    ext::property<html_or_svg_script_element_t> current_script;

    ext::property<std::unique_ptr<window_proxy>> default_view;
    ext::property<ext::string> design_mode;

    /* PERMISSIONS_POLICY */
    ext::property<std::unique_ptr<permissions_policy::permissions_policy_object>> permissions_policy;

    /* PAGE_VISIBILITY */
    ext::property<ext::boolean> hidden;
    ext::property<page_visibility::detail::visibility_state_t> visibility_state;

    /* FULLSCREEN */
    ext::property<ext::boolean> fullscreen_enabled;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

public cpp_operators:
    auto operator[](const ext::string& name) -> ranges::any_view<element*> override;

private js_slots:
    /* DEVICE_POSTURE */
    ext::number<double> s_current_posture;

private cpp_methods:
    /* HTML */
    [[nodiscard]] auto get_m_html_element() const -> html::elements::html_html_element*;
    [[nodiscard]] auto get_m_title_element() const -> html::elements::html_title_element*;

    /* FULLSCREEN */
    auto m_fullscreen_element() -> element*;

private cpp_properties:
    /* DOM */
    // std::unique_ptr<encoding::encoding> m_encoding = nullptr;
    ext::string m_type = "xml";
    ext::string m_mode = "no-quirks";
    ext::string m_origin;

    /* HTML */
    std::unique_ptr<html::detail::policy_container_t> m_policy_container;
    std::unique_ptr<html::detail::cross_origin_opener_policy_value_t> m_cross_origin_opener_policy;
    std::unique_ptr<permissions_policy::detail::internal_permissions_policy_t> m_permissions_policy;
    module_map_t m_module_map;
    ext::boolean m_is_initial = false;

    html::detail::document_load_timing_info_t& m_load_timing_info;
    html::detail::document_unload_timing_info_t& m_unload_timing_info;

    ext::set<element*> m_render_blocking_elements;
    std::unique_ptr<html::detail::browsing_context_t*> m_browsing_context;

    ext::boolean m_will_declaratively_refresh;

    ext::number<int> m_script_blocking_style_sheet_counter = 0;

    ext::map<html::detail::preload_key_t*, html::detail::preload_entry_t*> m_preloaded_resources;

    std::unique_ptr<intersection_observer::intersection_observer> m_lazy_load_intersection_observer;

    ext::map<html::detail::image_internals::available_image*, std::byte[]> m_list_of_available_images;

    ext::boolean m_iframe_load_in_progress_flag;
    ext::boolean m_mute_iframe_flag;

    /* FULLSCREEN */
    ext::vector<ext::tuple<ext::string, element*>> m_list_of_pending_fullscreen_events;

private cpp_accessors:
    /* DOM */
    [[nodiscard]] auto get_node_type() const -> ext::number<ushort> override {return DOCUMENT_NODE;}
    [[nodiscard]] auto get_node_name() const -> ext::string override {return "#document";}
    [[nodiscard]] auto get_node_value() const -> ext::string override {return "";}
    [[nodiscard]] auto get_text_content() const -> ext::string override {return "";}
    auto set_node_value(ext::string_view val) -> void override {};
    auto set_text_content(ext::string_view val) -> void override {}

    [[nodiscard]] auto get_compat_mode() const -> ext::string;
    [[nodiscard]] auto get_character_set() const -> ext::string;
    [[nodiscard]] auto get_doctype() const -> document_type*;
    [[nodiscard]] auto get_document_element() const -> element*;

    /* HTML */
    [[nodiscard]] auto get_last_modified() const -> ext::string;
    [[nodiscard]] auto get_cookie() const -> ext::string;
    [[nodiscard]] auto get_body() const -> html::elements::html_body_element*;
    [[nodiscard]] auto get_head() const -> html::elements::html_head_element*;
    [[nodiscard]] auto get_title() const -> ext::string;
    [[nodiscard]] auto get_images() const -> ranges::any_view<html::elements::html_image_element*>;
    [[nodiscard]] auto get_links() const -> ranges::any_view<html::elements::html_link_element*>;
    [[nodiscard]] auto get_forms() const -> ranges::any_view<html::elements::html_form_element*>;
    [[nodiscard]] auto get_scripts() const -> ranges::any_view<html::elements::html_script_element*>;
    [[nodiscard]] auto get_dir() const -> ext::string;

    auto set_ready_state(ext::string_view val) -> void;
    auto set_cookie(ext::string_view val) -> void;
    auto set_title(ext::string_view val) -> void;
    auto set_body(html::elements::html_body_element* val) -> void;

    /* PAGE_VISIBILITY */
    DEFINE_GETTER(hidden);
    DEFINE_GETTER(visibility_state);
};


#endif //SBROWSER2_DOCUMENT_HPP
