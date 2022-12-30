module;
#include "ext/macros.hpp"


export module apis.dom.xml_document:p;
import apis.dom.document;


DEFINE_PRIVATE_CLASS(dom, xml_document) final
        : dom::document_private
{
public:
    MAKE_QIMPL(xml_document);
};
