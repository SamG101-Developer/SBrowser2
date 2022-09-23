#ifndef SBROWSER2_XML_DOCUMENT_HPP
#define SBROWSER2_XML_DOCUMENT_HPP

#include "dom/nodes/document.hpp"
namespace dom::nodes {class xml_document;}

#include "dom/nodes/xml_document_private.hpp"


class dom::nodes::xml_document final
        : public document
{
public:
    xml_document();
    MAKE_PIMPL(xml_document);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_XML_DOCUMENT_HPP
