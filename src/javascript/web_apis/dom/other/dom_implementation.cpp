module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.dom_implementation;



auto dom::other::dom_implementation::create_document_type(
        ext::string&& qualified_name,
        ext::string&& public_id,
        ext::string&& system_id)
        const -> std::unique_ptr<nodes::document_type>
{
    ACCESS_PIMPL(const dom_implementation);
    detail::validate(qualified_name);

    // Create a DocumentType node and set its unique attributes, as well as setting the owner document of it to this dom
    // implementation's associated document.
    auto document_type = std::make_unique<nodes::document_type>();
    document_type->d_func()->node_document = d->document.get();
    document_type->d_func()->name = std::move(qualified_name);
    document_type->d_func()->public_id = std::move(public_id);
    document_type->d_func()->system_id = std::move(system_id);
    return document_type;
}


auto dom::other::dom_implementation::create_document(
        ext::string&& namespace_,
        ext::string&& qualified_name,
        std::unique_ptr<nodes::document_type>&& document_type)
        const -> std::unique_ptr<nodes::xml_document>
{
    // Create the document instance.
    auto document = std::make_unique<nodes::xml_document>();

    // Append a document element (Element) if a qualified name was presented; create an element with 'namespace_' and
    // 'qualified_name'.
    if (!qualified_name.empty())
        detail::append(std::make_unique<nodes::element>(), document.get()); // &document.create_element_ns(namespace_, qualified_name)

    // Append the 'document_type' (DocumentType) if it isn't nullptr to the document after the Element (conforms to
    // mutation algorithm constrains - Document can have an Element and DocumentType child)
    if (document_type)
        detail::append(std::move(document_type), document.get());

    // Set the document's 'content_type' based on the 'namespace_' parameter.
    string_switch(namespace_)
    {
        string_case(detail::HTML): document->d_func()->content_type = u"application/xhtml+xml";
        string_case(detail::SVG ): document->d_func()->content_type = u"application/svg+xml";
        string_default: document->d_func()->content_type = u"application/xml";
    }

    return std::move(document);
}


auto dom::other::dom_implementation::create_html_document(
        ext::string&& title)
        const -> std::unique_ptr<nodes::document>
{
    // Create the Document frame that will hold a basic "html -> head, body" structure; the content type is set to the
    // HTML content type, and the document type is set to HTML, signifying that the document is a HTML document.
    auto document = std::make_unique<nodes::document>();
    document->d_func()->content_type = u"text/html";
    document->d_func()->type = u"html";

    // Create a DocumentType node that is always the first child of a Document; name it "html", and set its document to
    // this node's owner document.
    auto doctype = std::make_unique<nodes::document_type>();
    doctype->d_func()->name = u"html";
    doctype->d_func()->node_document = document.get();

    // Begin the basic structure with a HTMLHtmlElement, containing a HTMLHeadElement (access previous element with
    // document->child_nodes()->at(...) - index 0 is the DocumentType node.
    detail::append(std::move(doctype), document.get());
    detail::append(detail::create_an_element(document.get(), u"html", detail::HTML), document.get());
    detail::append(detail::create_an_element(document.get(), u"head", detail::HTML), document->d_func()->child_nodes.at(1).get());

    // If there is a 'title', then add a HTMLTitleElement into the HTMLHeadElement, and a Text node into the
    // HTMLTitleElement, containing the 'title' text.
    if (!title.empty())
    {
        auto title_text = std::make_unique<nodes::text>(std::move(title));
        title_text->d_func()->node_document = document.get();
        detail::append(detail::create_an_element(document.get(), u"title", detail::HTML), document->d_func()->child_nodes.at(2).get());
        detail::append(std::move(title_text), document->d_func()->child_nodes.at(3).get());
    }

    // Add the HTMLBodyElement into the HTMLHtmlElement - this is where all the other nodes will be inserted into, as
    // the body acts as a container to the displayable elements.
    detail::append(detail::create_an_element(document.get(), u"body", detail::HTML), document->d_func()->child_nodes.at(1).get());
    return std::move(document);
}


auto dom::other::dom_implementation::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .function("createDocumentType", &dom_implementation::create_document_type)
        .function("createDocument", &dom_implementation::create_document)
        .function("createHTMLDocument", &dom_implementation::create_html_document)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
