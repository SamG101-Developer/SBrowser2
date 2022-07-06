#ifndef SBROWSER2_DOCUMENT_HPP
#define SBROWSER2_DOCUMENT_HPP

#include <web_apis/dom/nodes/node.hpp>
#include <web_apis/dom/mixins/document_or_element_node.hpp>
#include <web_apis/dom/mixins/document_or_shadow_root.hpp>
#include <web_apis/dom/mixins/non_element_parent_node.hpp>
#include <web_apis/dom/mixins/parentable_node.hpp>
#include <web_apis/dom/xpath/xpath_evaluator_base.hpp>
namespace dom::nodes {class document;}

#include <ext/map.hpp>
namespace dom::nodes {class attr;}
namespace dom::nodes {class cdata_section;}
namespace dom::nodes {class comment;}
namespace dom::nodes {class document_fragment;}
namespace dom::nodes {class document_type;}
namespace dom::nodes {class processing_instruction;}
namespace dom::nodes {class text;}
namespace dom::node_ranges {class range;}
namespace dom::node_iterators {class node_filter;}
namespace dom::node_iterators {class node_iterator;}
namespace dom::node_iterators {class tree_walker;}
namespace dom::other {class dom_implementation;}
namespace url {class url_object;}


class dom::nodes::document
        : public node
        , public mixins::document_or_element_node
        , public mixins::document_or_shadow_root
        , public mixins::non_element_parent_node
        , public mixins::parentable_node
        , public xpath::xpath_evaluator_base
{
public friends:
    friend struct mixins::document_or_element_node;

public constructors:
    document();

public js_methods:
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

public js_properties:
    ext::property<std::unique_ptr<url::url_object>> url;
    ext::property<ext::string> compat_mode;
    ext::property<ext::string> character_set;
    ext::property<ext::string> content_type;
    ext::property<document_type*> doctype;
    ext::property<std::unique_ptr<element>> document_element;
    ext::property<std::unique_ptr<other::dom_implementation>> implementation;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
//    std::unique_ptr<encoding::encoding> m_encoding = nullptr;
    ext::string m_type = "xml";
    ext::string m_mode = "no-quirks";
    ext::string m_origin;

private cpp_accessors:
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
};


#endif //SBROWSER2_DOCUMENT_HPP
