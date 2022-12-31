module;
#include "ext/macros.hpp"


export module apis.dom.xml_document;
import apis.dom.document;

IMPORT_ALL_TYPES(dom);


DEFINE_PUBLIC_CLASS(dom, xml_document) final
        : public dom::document
{
public friends:
    friend class dom::dom_implementation;

public constructors:
    DOM_CTORS(xml_document);
    MAKE_PIMPL(xml_document);
    MAKE_V8_AVAILABLE(WINDOW);
};
