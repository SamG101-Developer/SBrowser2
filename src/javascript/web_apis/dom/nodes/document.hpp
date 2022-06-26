#ifndef SBROWSER2_DOCUMENT_HPP
#define SBROWSER2_DOCUMENT_HPP

#include <web_apis/dom/nodes/node.hpp>
#include <web_apis/dom/mixins/document_or_element_node.hpp>
#include <web_apis/dom/mixins/document_or_shadow_root.hpp>
#include <web_apis/dom/mixins/non_element_parent_node.hpp>
#include <web_apis/dom/mixins/parentable_node.hpp>
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
namespace url {class url;}


class dom::nodes::document
        : public node
        , public mixins::document_or_element_node
        , public mixins::document_or_shadow_root
        , public mixins::non_element_parent_node
        , public mixins::parentable_node
{
public friends:
    friend struct mixins::document_or_element_node;

public constructors:
    document();

public js_methods:
    [[nodiscard]] auto create_element(const ext::string& local_name, ext::string_any_map_view options = {}) const -> element;
    [[nodiscard]] auto create_element_ns(const ext::string& namespace_, const ext::string& qualified_name, ext::string_any_map_view options) const -> element;
    [[nodiscard]] auto create_document_fragment() const -> document_fragment;
    [[nodiscard]] auto create_text_node(const ext::string& data) const -> text;
    [[nodiscard]] auto create_cdata_section_node(const ext::string& data) const -> cdata_section;
    [[nodiscard]] auto create_comment(const ext::string& data) const -> comment;
    [[nodiscard]] auto create_processing_instruction(const ext::string& target, const ext::string& data) const -> processing_instruction;
    [[nodiscard]] auto create_attribute(const ext::string& local_name) const -> attr;
    [[nodiscard]] auto create_attribute_ns(const ext::string& namespace_, const ext::string& qualified_name) const -> attr;

    auto create_range() -> node_ranges::range;
    auto create_node_iterator(node* root, ulong what_to_show = 0xFFFFFFFF, node_iterators::node_filter* filter = nullptr) -> node_iterators::node_iterator;
    auto create_tree_walker(node* root, ulong what_to_show = 0xFFFFFFFF, node_iterators::node_filter* filter = nullptr) -> node_iterators::tree_walker;

    auto import_node(node* new_node, bool deep = false) -> node*;
    auto adopt_node(node* new_node) -> node*;

public js_properties:
    ext::property<std::unique_ptr<url::url>> url;
    ext::property<ext::string> compat_mode;
    ext::property<ext::string> character_set;
    ext::property<ext::string> content_type;
    ext::property<document_type*> doctype;
    ext::property<std::unique_ptr<element>> document_element;
    ext::property<std::unique_ptr<other::dom_implementation>> implementation;

private cpp_properties:
    std::unique_ptr<encoding::encoding> m_encoding = nullptr;
    ext::string m_type = "xml";
    ext::string m_mode = "no-quirks";
    ext::string m_origin;

private cpp_accessors:
    [[nodiscard]] auto get_node_name() const -> ext::string override {return "#document";}

    [[nodiscard]] auto get_compat_mode() const -> ext::string;
    [[nodiscard]] auto get_character_set() const -> ext::string;
    [[nodiscard]] auto get_doctype() const -> document_type*;
    [[nodiscard]] auto get_document_element() const -> element*;
};


#endif //SBROWSER2_DOCUMENT_HPP
