module;
#include "ext/macros.hpp"


module apis.dom.xml_document;

import ext.core;


dom::nodes::xml_document::xml_document()
{
    INIT_PIMPL(xml_document);
}


auto dom::nodes::xml_document::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<document>()
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}