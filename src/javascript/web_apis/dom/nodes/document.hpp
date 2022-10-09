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
namespace dom::nodes {class document_private;}

#include "ext/concepts.hpp"
#include "ext/map.hpp"
#include "ext/promise.hpp"
#include "ext/set.hpp"
#include "ext/tuple.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"
#include <range/v3/view/any_view.hpp>

#include INCLUDE_INNER_TYPES(css/css_animation_worklet)
#include INCLUDE_INNER_TYPES(css/css_layout)
#include INCLUDE_INNER_TYPES(css/css_web_animations)
#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(permissions_policy)
#include INCLUDE_INNER_TYPES(page_visibility)
#include INCLUDE_INNER_TYPES(url)

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

namespace css::css_web_animation {class document_timeline;}
namespace encoding {class encoding;}
namespace intersection_observer {class intersection_observer;}
namespace permissions_policy {class permissions_policy_object;}
namespace selection {class selection;}
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
public constructors:
    document();
    MAKE_PIMPL(document);
    MAKE_V8_AVAILABLE;
    auto operator[](const ext::string& name) -> ranges::any_view<element*>& override;

public js_methods:
    /* [DOM] */
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

    auto import_node(node* new_node, ext::boolean deep = false) -> node*;
    auto adopt_node(node* new_node) -> node*;

    /* [HTML] */
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

    /* [POINTER_LOCK] */
    auto exit_pointer_lock() -> void;

    /* [FULLSCREEN] */
    auto exit_fullscreen() -> ext::promise<void>;

    /* [SELECTION] */
    auto get_selection() -> selection::selection*;

    /* [CSS_BOX_TREE] */
    auto layout_now() -> void;

private js_properties:

    /* [HTML] */
    ext::property<std::unique_ptr<html::other::location>> location;
    ext::property<ext::string> domain;
    ext::property<ext::string> referrer;
    ext::property<ext::string> cookie;
    ext::property<ext::string> last_modified;
    ext::property<ext::string> ready_state;
    ext::property<ext::string> title; // TODO : CE_REACTIONS
    ext::property<ext::string> dir; // TODO : CE_REACTIONS

    ext::property<html::elements::html_body_element*> body; // TODO : CE_REACTIONS
    ext::property<html::elements::html_head_element*> head; // TODO : CE_REACTIONS
    ext::property<ranges::any_view<html::elements::html_image_element*>> images;
    ext::property<ranges::any_view<html::elements::html_link_element*>> links;
    ext::property<ranges::any_view<html::elements::html_form_element*>> forms;
    ext::property<ranges::any_view<html::elements::html_script_element*>> scripts;
    ext::property<detail::html_or_svg_script_element_t> current_script;

    ext::property<window_proxy*> default_view;
    ext::property<ext::string> design_mode;

    /* [PERMISSIONS_POLICY] */
    ext::property<std::unique_ptr<permissions_policy::permissions_policy_object>> permissions_policy;

    /* [PAGE_VISIBILITY] */
    ext::property<ext::boolean> hidden;
    ext::property<page_visibility::detail::visibility_state_t> visibility_state;

    /* [FULLSCREEN] */
    ext::property<ext::boolean> fullscreen_enabled;

    /* [CSS_WEB_ANIMATIONS] */
    ext::property<css::css_web_animation::document_timeline*> timeline;

private js_properties:
    /* [DOM] */
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return DOCUMENT_NODE;}
    DEFINE_GETTER(node_name, ext::string) override {return "#document";}
    DEFINE_GETTER(node_value, ext::string) override {return "";}
    DEFINE_GETTER(text_content, ext::string) override {return "";}

    DEFINE_SETTER(node_value, ext::string) override {};
    DEFINE_SETTER(text_content, ext::string) override {}

    DEFINE_GETTER(url, ext::string);
    DEFINE_GETTER(compat_mode, ext::string);
    DEFINE_GETTER(character_set, ext::string);
    DEFINE_GETTER(content_type, ext::string);
    DEFINE_GETTER(doctype, document_type*);
    DEFINE_GETTER(document_element, element*);
    DEFINE_GETTER(implementation, other::dom_implementation*);

    /* [HTML] */
    DEFINE_GETTER(last_modified);
    DEFINE_GETTER(cookie);
    DEFINE_GETTER(body);
    DEFINE_GETTER(head);
    DEFINE_GETTER(title);
    DEFINE_GETTER(images);
    DEFINE_GETTER(links);
    DEFINE_GETTER(forms);
    DEFINE_GETTER(scripts);
    DEFINE_GETTER(dir);
    DEFINE_GETTER(design_mode);
    DEFINE_GETTER(domain);

    DEFINE_SETTER(ready_state);
    DEFINE_SETTER(cookie);
    DEFINE_SETTER(title);
    DEFINE_SETTER(body);
    DEFINE_SETTER(design_mode);
    DEFINE_SETTER(domain);

    /* [PAGE_VISIBILITY] */
    DEFINE_GETTER(hidden);
    DEFINE_GETTER(visibility_state);

    DEFINE_CUSTOM_SETTER(visibility_state);

    /* [CSS_WEB_ANIMATIONS] */
    DEFINE_GETTER(timeline);
};


#endif //SBROWSER2_DOCUMENT_HPP
