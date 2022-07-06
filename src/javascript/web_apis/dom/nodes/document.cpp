#include "document.hpp"

#include <ext/casting.hpp>
#include <ext/ranges.hpp>

#include <javascript/environment/realms_2.hpp>

#include <web_apis/dom/detail/exception_internals.hpp>
#include <web_apis/dom/detail/customization_internals.hpp>
#include <web_apis/dom/detail/namespace_internals.hpp>
#include <web_apis/dom/detail/node_internals.hpp>

#include <web_apis/dom/nodes/attr.hpp>
#include <web_apis/dom/nodes/cdata_section.hpp>
#include <web_apis/dom/nodes/comment.hpp>
#include <web_apis/dom/nodes/document_fragment.hpp>
#include <web_apis/dom/nodes/element.hpp>
#include <web_apis/dom/nodes/processing_instruction.hpp>
#include <web_apis/dom/nodes/shadow_root.hpp>

#include <web_apis/dom/other/dom_implementation.hpp>
#include <web_apis/dom/ranges/range.hpp>
#include <web_apis/url/url.hpp>

#include <range/v3/algorithm/contains.hpp>

#include <QtCore/QPointer>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollArea>


dom::nodes::document::document()
        : url{std::make_unique<url::url_object>("about:blank")}
        , implementation{std::make_unique<other::dom_implementation>()}
        , content_type{"application/xml"}
{
    bind_get(compat_mode);
    bind_get(character_set);
    bind_get(doctype);
    bind_get(document_element);

    JS_REALM_GET_SURROUNDING(this)
    m_origin = javascript::environment::realms_2::get<ext::string>(surrounding_global_object, "origin");

    auto rendered_widget = QPointer<QScrollArea>{};
    rendered_widget->setWidget(QPointer<QWidget>{});
    rendered_widget->widget()->setLayout(QPointer<QVBoxLayout>{});
    rendered_widget->setWidgetResizable(true);
    m_rendered_widget = rendered_widget;
}


auto dom::nodes::document::create_element(
        ext::string_view local_name,
        ext::string_any_map_view options)
        const -> element
{
    ce_reactions_method_def
        // create the html adjusted local name and namespace, and get the 'is' option from the options dictionary - set it
        // to the empty string otherwise
        auto html_adjusted_local_name = detail::namespace_internals::html_adjust_string(local_name, m_type == "html");
        auto html_adjusted_namespace_ = m_type == "html" || content_type() == "application/xhtml+xml" ? detail::namespace_internals::HTML : "";
        auto is = options.at("is").value_to_or<ext::string>("");

        // create the Element node with the html adjusted variables
        return detail::customization_internals::create_an_element(this, html_adjusted_local_name, html_adjusted_namespace_, "", is, true);
    ce_reactions_method_exe
}


auto dom::nodes::document::create_element_ns(
        ext::string_view namespace_,
        ext::string_view qualified_name,
        ext::string_any_map_view options)
        const -> element
{
    ce_reactions_method_def
        // determine the 'prefix' and 'local_name' from the 'namespace_' and 'qualified_name', using the detail
        // 'validate_and_extract(...)' method
        auto [prefix, local_name] = detail::namespace_internals::validate_and_extract(namespace_, qualified_name);
        auto is = options.at("is").value_to_or<ext::string>("");

        // create the Element node with the html adjusted variables
        return detail::customization_internals::create_an_element(this, local_name, namespace_, prefix, is, true);
    ce_reactions_method_exe
}


auto dom::nodes::document::create_document_fragment()
        const -> document_fragment
{
    // create a DocumentFragment node, and set its owner document to this document
    document_fragment node;
    node.owner_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_text_node(
        ext::string_view data)
        const -> text
{
    // create a Text node, and set its data and owner document to the 'data' parameter and this document
    text node;
    node.data = data;
    node.owner_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_cdata_section_node(
        ext::string_view data)
        const -> cdata_section
{
    detail::exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
            [this] {return m_type == "html";},
            "Cannot create a CDataSection node in a HTML Document");

    detail::exception_internals::throw_v8_exception_formatted<INVALID_CHARACTER_ERR>(
            [data] {return ranges::contains(data, "]]>");},
            "Cannot create a CDataSection node with ']]>' in the data");

    cdata_section node;
    node.data = data;
    node.owner_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_comment(
        ext::string_view data)
        const -> comment
{
    comment node;
    node.data = data;
    node.owner_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_processing_instruction(
        ext::string_view target,
        ext::string_view data)
        const -> processing_instruction
{
    detail::exception_internals::throw_v8_exception_formatted<INVALID_CHARACTER_ERR>(
            [data] {return ranges::contains(data, "?>");},
            "Cannot create a CDataSection node with '?>' in the data");

    processing_instruction node;
    node.data = data;
    node.target = target;
    node.owner_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_attribute(
        ext::string_view local_name)
        const -> attr
{
    auto html_adjusted_local_name = m_type == "html" ? local_name | ranges::views::lowercase() : local_name;

    attr node;
    node.local_name = html_adjusted_local_name;
    node.owner_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_attribute_ns(
        ext::string_view namespace_,
        ext::string_view qualified_name)
        const -> attr
{
    auto [prefix, local_name] = detail::namespace_internals::validate_and_extract(namespace_, qualified_name);

    attr node;
    node.local_name = std::move(local_name);
    node.prefix = std::move(prefix);
    node.namespace_uri = namespace_;
    node.owner_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_range()
        const -> node_ranges::range
{
    node_ranges::range live_range;

    std::tie(live_range.start_container, live_range.start_offset) = std::make_tuple(const_cast<document*>(this), 0);
    std::tie(live_range.end_container  , live_range.end_offset  ) = std::make_tuple(const_cast<document*>(this), 0);
    return live_range;
}


auto dom::nodes::document::import_node(
        node* new_node,
        ext::boolean_view deep)
        -> node*
{
    ce_reactions_method_def
        detail::exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
                [new_node] {return ext::multi_cast<nodes::document*, nodes::shadow_root*>(new_node);},
                "Node being imported cannot be a Document or ShadowRoot");

        // to import a node, a clone of the node is made, with the Document set tot this node; the node is basically copied
        // into this Document
        return detail::node_internals::clone(new_node, this, true);
    ce_reactions_method_exe
}


auto dom::nodes::document::adopt_node(
        node* new_node)
        -> node*
{
    ce_reactions_method_def
        detail::exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
                [new_node] {return ext::multi_cast<nodes::document*>(new_node);},
                "Node being imported cannot be a Document");

        detail::exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                [new_node] {return ext::multi_cast<nodes::shadow_root*>(new_node);},
                "Node being imported cannot be a ShadowRoot");

        // to adopt a node, the node is moved, not copied, from its current Document node to this Document Node; no cloning
        // takes place
        return detail::node_internals::adopt(new_node, this);
    ce_reactions_method_exe
}
