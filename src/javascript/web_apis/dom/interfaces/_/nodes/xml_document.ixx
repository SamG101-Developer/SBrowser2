module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/macros.hpp"
#include "ext/macros/constructors.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.xml_document;
import apis.dom.document;

import apis.dom.types;
import ext.core;
import js.env.module_type;


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
