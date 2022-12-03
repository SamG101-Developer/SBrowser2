#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_XML_DOCUMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_XML_DOCUMENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/nodes/document_private.hpp"


DEFINE_PRIVATE_CLASS(dom::nodes, xml_document)
        : document_private
{
    MAKE_QIMPL(xml_document);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_XML_DOCUMENT_PRIVATE_HPP
