#include "dom_implementation.hpp"

#include <web_apis/dom/detail/customization_internals.hpp>
#include <web_apis/dom/detail/mutation_internals.hpp>
#include <web_apis/dom/detail/namespace_internals.hpp>
#include <web_apis/dom/nodes/document.hpp>
#include <web_apis/dom/nodes/element.hpp>
#include <web_apis/dom/nodes/document_type.hpp>
#include <web_apis/dom/nodes/xml_document.hpp>


auto dom::other::dom_implementation::create_document_type(
        ext::string_view qualified_name,
        ext::string_view public_id,
        ext::string_view system_id)
        const -> nodes::document_type
{
    detail::namespace_internals::validate(qualified_name);

    // create a DocumentType node and set its unique attributes, as well as setting the owner document of it to this dom
    // implementation's associated document
    nodes::document_type document_type;
    document_type.owner_document = m_associated_document;
    document_type.name = qualified_name;
    document_type.public_id = public_id;
    document_type.system_id = system_id;
    return document_type;
}


auto dom::other::dom_implementation::create_document(
        ext::string_view namespace_,
        ext::string_view qualified_name,
        nodes::document_type* document_type)
        const -> nodes::xml_document
{
    // create the document instance
    nodes::xml_document document;

    // append a document element (Element) if a qualified name was presented; create an element with 'namespace_' and
    // 'qualified_name'
    if (!qualified_name.empty())
        detail::mutation_internals::append(&document.create_element_ns(namespace_, qualified_name), &document);

    // append the 'document_type' (DocumentType) if it isn't nullptr to the document after the Element (conforms to
    // mutation algorithm constrains - Document can have an Element and DocumentType child)
    if (document_type)
        detail::mutation_internals::append(document_type, &document);

    // set the document's 'content_type' based on the 'namespace_' parameter
    string_switch(namespace_)
    {
        string_case(detail::namespace_internals::HTML): document.content_type = "application/xhtml+xml";
        string_case(detail::namespace_internals::SVG ): document.content_type = "application/svg+xml";
        string_default: document.content_type = "application/xml";
    }

    return document;
}


auto dom::other::dom_implementation::create_html_document(
        ext::string_view title)
        const -> nodes::document*
{
    nodes::document document{};
    document.content_type = "text/html";
    document.m_type = "html";

    auto* doctype = new nodes::document_type{};
    doctype->name = "html";
    doctype->owner_document = &document;

    detail::mutation_internals::append(doctype, &document);
    detail::mutation_internals::append(detail::customization_internals::create_an_element(&document, "title", detail::namespace_internals::HTML), &document);
    detail::mutation_internals::
}
