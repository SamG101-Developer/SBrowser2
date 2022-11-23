#ifndef SBROWSER2_XML_DOCUMENT_HPP
#define SBROWSER2_XML_DOCUMENT_HPP

#include "dom/nodes/document.hpp"
namespace dom::nodes {class xml_document;}
namespace dom::nodes {class xml_document_private;}

namespace dom::other {class dom_implementation;}


class dom::nodes::xml_document final
        : public document
{
public friends:
    friend class dom::other::dom_implementation;

public constructors:
    DOM_CTORS(xml_document);
    MAKE_PIMPL(xml_document);
    MAKE_V8_AVAILABLE(WINDOW);
};


#endif //SBROWSER2_XML_DOCUMENT_HPP
