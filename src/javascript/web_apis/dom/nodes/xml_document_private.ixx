module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.xml_document_private;
import apis.dom.document_private;


DEFINE_PRIVATE_CLASS(dom, xml_document) final
        : dom::document_private
{
public:
    MAKE_QIMPL(xml_document);
};
