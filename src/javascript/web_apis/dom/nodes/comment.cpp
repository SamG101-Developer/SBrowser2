module;
#include "ext/macros/custom_operator.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include "javascript/macros/errors.hpp"
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.dom.comment;
import apis.dom.comment_private;
import apis.dom.window;
import apis.dom.window_private;
import apis.dom.types;

import ext.string;
import ext.tuple;

import js.env.module_type;
import js.env.realms;
import js.env.slots;


dom::comment::comment(ext::string&& new_data)
{
    INIT_PIMPL; ACCESS_PIMPL;
    auto e = js::env::env::relevant(this);

    d->node_document = e.cpp.global<window*>()->d_func()->document.get();
    d->data = std::move(new_data);
}


auto dom::comment::get_node_name() const -> ext::string
{
    // The 'node_name' getter returns the fixed string "#comment". Apply custom element reactions to this getter.
    _CE_REACTIONS_METHOD_DEF
        return u"#comment";
    _CE_REACTIONS_METHOD_EXE
}


auto dom::comment::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<character_data>()
        .ctor<>()
        .ctor<ext::string&&>()
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
