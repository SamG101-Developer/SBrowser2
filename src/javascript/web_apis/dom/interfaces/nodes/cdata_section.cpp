module;
#include "ext/macros/custom_operator.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include "javascript/macros/errors.hpp"


module apis.dom.cdata_section;
import apis.dom.types;

import ext.core;

import js.env.module_type;
import js.env.realms;
import js.env.slots;


dom::cdata_section::cdata_section()
{
    INIT_PIMPL;
}


auto dom::cdata_section::get_node_name() const -> ext::string
{
    // The 'node_name' getter returns the fixed string "#cdata-section". Apply custom element reactions to this getter.
    _CE_REACTIONS_METHOD_DEF
        return u"#cdata-section";
    _CE_REACTIONS_METHOD_EXE
}


auto dom::cdata_section::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<text>()
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
