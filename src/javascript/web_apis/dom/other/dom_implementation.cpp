#include "dom_implementation.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/detail/namespace_internals.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/document_type.hpp"
#include "dom/nodes/text.hpp"
#include "dom/nodes/xml_document.hpp"


auto dom::other::dom_implementation::create_document_type(
        ext::string&& qualified_name,
        ext::string&& public_id,
        ext::string&& system_id)
        const -> nodes::document_type
{
    detail::validate(qualified_name);

    // create a DocumentType node and set its unique attributes, as well as setting the owner document of it to this dom
    // implementation's associated document
    nodes::document_type document_type;
    document_type.owner_document = m_associated_document;
    document_type.name = std::move(qualified_name);
    document_type.public_id = std::move(public_id);
    document_type.system_id = std::move(system_id);
    return document_type;
}


auto dom::other::dom_implementation::create_document(
        ext::string&& namespace_,
        ext::string&& qualified_name,
        nodes::document_type* document_type)
        const -> nodes::xml_document
{
    // create the document instance
    nodes::xml_document document {};

    // append a document element (Element) if a qualified name was presented; create an element with 'namespace_' and
    // 'qualified_name'
    if (!qualified_name.empty())
        detail::append(nodes::element{}, &document); // &document.create_element_ns(namespace_, qualified_name)

    // append the 'document_type' (DocumentType) if it isn't nullptr to the document after the Element (conforms to
    // mutation algorithm constrains - Document can have an Element and DocumentType child)
    if (document_type)
        detail::append(document_type, &document);

    // set the document's 'content_type' based on the 'namespace_' parameter
    string_switch(namespace_)
    {
        string_case(detail::HTML): document.content_type = "application/xhtml+xml";
        string_case(detail::SVG ): document.content_type = "application/svg+xml";
        string_default: document.content_type = "application/xml";
    }

    return document;
}


auto dom::other::dom_implementation::create_html_document(
        ext::string&& title)
        const -> nodes::document*
{
    // create the Document frame that will hold a basic "html -> head, body" structure; the content type is set to the
    // HTML content type, and the document type is set to HTML, signifying that the document is a HTML document
    nodes::document document{};
    document.content_type = "text/html";
    document.m_type = "html";

    // create a DocumentType node that is always the first child of a Document; name it "html", and set its document to
    // this node's owner document
    nodes::document_type doctype{};
    doctype.name = "html";
    doctype.owner_document = &document;

    // begin the basic structure with a HTMLHtmlElement, containing a HTMLHeadElement (access previous element with
    // document->child_nodes()->at(...) - index 0 is the DocumentType node
    detail::append(&doctype, &document);
    detail::append(detail::create_an_element(&document, "html", detail::HTML), &document);
    detail::append(detail::create_an_element(&document, "head", detail::HTML), document.child_nodes()->at(1));

    // if there is a 'title', then add a HTMLTitleElement into the HTMLHeadElement, and a Text node into the
    // HTMLTitleElement, containing the 'title' text
    if (!title.empty())
    {
        nodes::text title_text {title}; title_text.owner_document = &document;
        detail::append(detail::create_an_element(&document, "title", detail::HTML), document.child_nodes()->at(2));
        detail::append(&title_text, document.child_nodes()->at(3));
    }

    // add the HTMLBodyElement into the HTMLHtmlElement - this is where all the other nodes will be inserted into, as
    // the body acts as a container to the displayable elements
    detail::append(detail::create_an_element(&document, "body", detail::HTML), document.child_nodes()->at(1));
}
