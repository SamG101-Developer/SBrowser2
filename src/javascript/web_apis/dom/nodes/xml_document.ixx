module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/constructors.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.xml_document;
import apis.dom.document;

import ext.tuple;
import js.env.module_type;

namespace dom {class dom_implementation;}


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
