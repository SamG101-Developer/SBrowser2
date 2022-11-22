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
#include "ext/ranges.hpp"
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

namespace dom::mixins {class document_or_element_node;}
namespace dom::nodes {class attr;}
namespace dom::nodes {class cdata_section;}
namespace dom::nodes {class comment;}
namespace dom::nodes {class document_fragment;}
namespace dom::nodes {class document_type;}
namespace dom::nodes {class processing_instruction;}
namespace dom::nodes {class text;}
namespace dom::nodes {class window_proxy;}
namespace dom::other {class dom_implementation;}

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
public friends:
    friend class dom::mixins::document_or_element_node;
    friend class dom::nodes::node;
    friend class dom::other::dom_implementation;

public constructors:
    DOM_CTORS(document);
    MAKE_PIMPL(document);
    MAKE_V8_AVAILABLE;
    auto operator[](const ext::string& name) -> ranges::any_view<element*>& override;

public js_methods:
    /* [DOM] */
    _EXT_NODISCARD auto create_element(ext::string&& local_name, ext::map<ext::string, ext::any>&& options = {}) -> std::unique_ptr<element>;
    _EXT_NODISCARD auto create_element_ns(ext::string&& namespace_, ext::string&& qualified_name, ext::map<ext::string, ext::any>&& options = {}) -> std::unique_ptr<element>;
    _EXT_NODISCARD auto create_document_fragment() -> std::unique_ptr<document_fragment>;
    _EXT_NODISCARD auto create_text_node(ext::string&& data) -> std::unique_ptr<text>;
    _EXT_NODISCARD auto create_cdata_section_node(ext::string&& data) -> std::unique_ptr<cdata_section>;
    _EXT_NODISCARD auto create_comment(ext::string&& data) -> std::unique_ptr<comment>;
    _EXT_NODISCARD auto create_processing_instruction(ext::string&& target, ext::string&& data) -> std::unique_ptr<processing_instruction>;
    _EXT_NODISCARD auto create_attribute(ext::string&& local_name) -> std::unique_ptr<attr>;
    _EXT_NODISCARD auto create_attribute_ns(ext::string&& namespace_, ext::string&& qualified_name) -> std::unique_ptr<attr>;

    _EXT_NODISCARD auto create_range() -> std::unique_ptr<node_ranges::range>;
    auto create_node_iterator(node* root, ulong what_to_show = 0xFFFFFFFF, node_iterators::node_filter* filter = nullptr) -> std::unique_ptr<node_iterators::node_iterator>;
    auto create_tree_walker(node* root, ulong what_to_show = 0xFFFFFFFF, node_iterators::node_filter* filter = nullptr) -> std::unique_ptr<node_iterators::tree_walker>;

    auto import_node(node* new_node, ext::boolean deep = false) -> node*;
    auto adopt_node(node* new_node) -> node*;

    /* [HTML] */
    auto open() -> document*;
    auto open(ext::string_view url, ext::string_view name, ext::string_view features) -> window_proxy*;
    auto close() -> void;
    auto write(ext::type_is<ext::string> auto&&... text) -> void;
    auto write_ln(ext::type_is<ext::string> auto&&... text) -> void;

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
    DEFINE_GETTER(node_name, ext::string) override {return u"#document";}
    DEFINE_GETTER(node_value, ext::string) override {return u"";}
    DEFINE_GETTER(text_content, ext::string) override {return u"";}

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
    DEFINE_GETTER(location, html::other::location*);
    DEFINE_GETTER(domain, ext::string);
    DEFINE_GETTER(referrer, ext::string_view);
    DEFINE_GETTER(cookie, ext::string);
    DEFINE_GETTER(ready_state, html::detail::document_readiness_state_t);
    DEFINE_GETTER(title, ext::string);
    DEFINE_GETTER(dir, html::detail::directionality_t);
    DEFINE_GETTER(body, html::elements::html_body_element*);
    DEFINE_GETTER(head, html::elements::html_head_element*);
    DEFINE_GETTER(images, ranges::any_helpful_view<html::elements::html_image_element*>);
    DEFINE_GETTER(links, ranges::any_helpful_view<html::elements::html_element*>);
    DEFINE_GETTER(forms, ranges::any_helpful_view<html::elements::html_form_element*>);
    DEFINE_GETTER(scripts, ranges::any_helpful_view<html::elements::html_script_element*>);
    DEFINE_GETTER(current_script, html::detail::html_or_svg_image_element_t);
    DEFINE_GETTER(default_view, window_proxy*);
    DEFINE_GETTER(design_mode, ext::boolean);

    DEFINE_SETTER(domain, ext::string);
    DEFINE_SETTER(cookie, ext::string);
    DEFINE_GETTER(last_modified, ext::string);
    DEFINE_SETTER(title, ext::string);
    DEFINE_SETTER(dir, html::detail::directionality_t);
    DEFINE_SETTER(body, html::elements::html_body_element*);
    DEFINE_SETTER(design_mode, ext::boolean);

    /* [PAGE_VISIBILITY] */ // TODO
    DEFINE_GETTER(hidden, ext::boolean);
    DEFINE_GETTER(visibility_state, page_visibility::detail::visibility_state_t);

    DEFINE_SETTER(visibility_state, page_visibility::detail::visibility_state_t);

    /* [CSS_WEB_ANIMATIONS] */ // TODO
    DEFINE_GETTER(timeline);
};


#endif //SBROWSER2_DOCUMENT_HPP
