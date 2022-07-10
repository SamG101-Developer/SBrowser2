#ifndef SBROWSER2_DOCUMENT_HPP
#define SBROWSER2_DOCUMENT_HPP

#include "range/v3/view/any_view.hpp"
#include <web_apis/dom/nodes/node.hpp>
#include <web_apis/dom/mixins/document_or_element_node.hpp>
#include <web_apis/dom/mixins/document_or_shadow_root.hpp>
#include <web_apis/dom/mixins/non_element_parent_node.hpp>
#include <web_apis/dom/mixins/parentable_node.hpp>
#include <web_apis/dom/xpath/xpath_evaluator_base.hpp>
#include <ext/map_like.hpp>
namespace dom::nodes {class document;}

#include <ext/concepts.hpp>
#include <ext/map.hpp>
#include <ext/set.hpp>
#include <url/url.hpp>
#include <ext/vector.hpp>
#include <range/v3/view/any_view.hpp>
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

namespace html::detail::policy_internals {struct cross_origin_opener_policy_value;}
namespace html::detail::policy_internals {struct policy_container;}
namespace html::detail::context_internals {struct browsing_context;}
namespace html::detail::document_internals {struct document_load_timing_info;}
namespace html::detail::document_internals {struct document_unload_timing_info;}

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

namespace permissions_policy {class permissions_policy;}
namespace svg::elements {class svg_script_element;}


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
    using module_map = ext::map<
            std::tuple<ext::string, url::url_object>,
            ext::string>;

    using html_or_svg_script_element = std::variant<
            std::unique_ptr<html::elements::html_script_element>,
            std::unique_ptr<svg::elements::svg_script_element>>;

public friends:
    friend struct mixins::document_or_element_node;

public constructors:
    document();

public js_methods:
    /* DOM */
    [[nodiscard]] auto create_element(ext::string_view local_name, ext::string_any_map_view options = {}) const -> element;
    [[nodiscard]] auto create_element_ns(ext::string_view namespace_, ext::string_view qualified_name, ext::string_any_map_view options) const -> element;
    [[nodiscard]] auto create_document_fragment() const -> document_fragment;
    [[nodiscard]] auto create_text_node(ext::string_view data) const -> text;
    [[nodiscard]] auto create_cdata_section_node(ext::string_view data) const -> cdata_section;
    [[nodiscard]] auto create_comment(ext::string_view data) const -> comment;
    [[nodiscard]] auto create_processing_instruction(ext::string_view target, ext::string_view data) const -> processing_instruction;
    [[nodiscard]] auto create_attribute(ext::string_view local_name) const -> attr;
    [[nodiscard]] auto create_attribute_ns(ext::string_view namespace_, ext::string_view qualified_name) const -> attr;

    [[nodiscard]] auto create_range() const -> node_ranges::range;
    auto create_node_iterator(node* root, ulong what_to_show = 0xFFFFFFFF, node_iterators::node_filter* filter = nullptr) const -> node_iterators::node_iterator;
    auto create_tree_walker(node* root, ulong what_to_show = 0xFFFFFFFF, node_iterators::node_filter* filter = nullptr) const -> node_iterators::tree_walker;

    auto import_node(node* new_node, ext::boolean_view deep = false) -> node*;
    auto adopt_node(node* new_node) -> node*;

    /* HTML */
    auto open() -> document*;
    auto open(ext::string_view url, ext::string_view name, ext::string_view features) -> window_proxy*;
    auto close() -> void;
    auto write(type_is<ext::string> auto&&... text) -> void;
    auto write_ln(type_is<ext::string> auto&&... text) -> void;

    auto has_focus() -> ext::boolean;
    auto queryCommandEnabled(ext::string_view commandId) -> ext::boolean;
    auto queryCommandIndeterm(ext::string_view commandId) -> ext::boolean;
    auto queryCommandState(ext::string_view commandId) -> ext::boolean;
    auto queryCommandSupported(ext::string_view commandId) -> ext::boolean;
    auto queryCommandValue(ext::string_view commandId) -> ext::boolean;

public js_properties:
    /* DOM */
    ext::property<std::unique_ptr<url::url_object>> url;
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
    ext::property<ext::string, _T> title;
    ext::property<ext::string, _T> dir;

    ext::property<std::unique_ptr<html::elements::html_body_element>, _T> body;
    ext::property<std::unique_ptr<html::elements::html_head_element>, _T> head;
    ext::property<ranges::any_view<html::elements::html_image_element*>> images;
    ext::property<ranges::any_view<html::elements::html_link_element*>> links;
    ext::property<ranges::any_view<html::elements::html_form_element*>> forms;
    ext::property<ranges::any_view<html::elements::html_script_element*>> scripts;
    ext::property<html_or_svg_script_element> current_script;

    ext::property<std::unique_ptr<window_proxy>> default_view;
    ext::property<ext::string> design_mode;
    ext::property<ext::boolean> hidden;
    ext::property<ext::string> visibility_state;

    /* PERMISSIONS_POLICY */
    ext::property<std::unique_ptr<permissions_policy::permissions_policy>> permissions_policy;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

public cpp_operators:
    virtual auto operator[](const ext::string& name) -> ranges::any_view<element*> override;

private cpp_methods:
    auto get_m_html_element() const -> html::elements::html_html_element*;
    auto get_m_title_element() const -> html::elements::html_title_element*;

private cpp_properties:
    /* DOM */
//    std::unique_ptr<encoding::encoding> m_encoding = nullptr;
    ext::string m_type = "xml";
    ext::string m_mode = "no-quirks";
    url::url_object m_origin;

    /* HTML */
    std::unique_ptr<html::detail::policy_internals::policy_container> m_policy_container;
    std::unique_ptr<html::detail::policy_internals::cross_origin_opener_policy_value> m_cross_origin_opener_policy;
    std::unique_ptr<permissions_policy::permissions_policy> m_permissions_policy;
    module_map m_module_map;
    ext::boolean m_is_initial = false;

    html::detail::document_internals::document_load_timing_info& m_load_timing_info;
    html::detail::document_internals::document_unload_timing_info& m_unload_timing_info;

    ext::set<element*> m_render_blocking_elements;
    std::shared_ptr<html::detail::context_internals::browsing_context*> m_browsing_context;

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
    auto get_body() const -> html::elements::html_body_element*;
    auto get_head() const -> html::elements::html_head_element*;
    auto get_title() const -> ext::string;
    auto get_images() const -> ranges::any_view<html::elements::html_image_element*>;
    auto get_links() const -> ranges::any_view<html::elements::html_link_element*>;
    auto get_forms() const -> ranges::any_view<html::elements::html_form_element*>;
    auto get_scripts() const -> ranges::any_view<html::elements::html_script_element*>;
    auto get_dir() const -> ext::string;

    auto set_ready_state(ext::string_view val) -> void;
    auto set_cookie(ext::string_view val) -> void;
    auto set_title(ext::string_view val) -> void;
    auto set_body(html::elements::html_body_element* val) -> void;
};


#endif //SBROWSER2_DOCUMENT_HPP
