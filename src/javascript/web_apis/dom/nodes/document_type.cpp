module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <tuplet/tuple.hpp>
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.dom.document_type;
import apis.dom.document_type_private;
import apis.dom.node;
import apis.dom.mixins.child_node;

import ext.string;
import ext.tuple;

import js.env.module_type;


dom::document_type::document_type()
{
    INIT_PIMPL;
}


auto dom::document_type::get_node_name() const -> ext::string
{
    // The 'node_name' getter returns the equivalent 'node_name' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->name;
}


auto dom::document_type::get_name() const -> ext::string_view
{
    // The 'name' getter returns the equivalent 'name' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->name;
}


auto dom::document_type::get_public_id() const -> ext::string_view
{
    // The 'public_id' getter returns the equivalent 'public_id' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->public_id;
}


auto dom::document_type::get_system_id() const -> ext::string_view
{
    // The 'system_id' getter returns the equivalent 'system_id' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->system_id;
}


auto dom::document_type::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<node>()
        .inherit<child_node>()
        .property("name", &document_type::get_name)
        .property("publicId", &document_type::get_public_id)
        .property("systemId", &document_type::get_system_id)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
