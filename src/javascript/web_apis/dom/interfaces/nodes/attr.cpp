module;
#include "ext/macros.hpp"
#include <v8-exception.h>


module apis.dom.attr;
import apis.dom.types;

import ext.core;

import js.env.module_type;
import js.env.realms;
import js.env.slots;


dom::attr::attr()
{
    INIT_PIMPL; ACCESS_PIMPL;
    d->element = nullptr;
}


auto dom::attr::get_node_value() const -> ext::string
{
    // The 'node_value' getter returns the equivalent 'value' attribute value that is stored in the private class. Apply
    // custom element reactions to this getter.
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->value;
    _CE_REACTIONS_METHOD_EXE
}


auto dom::attr::get_text_content() const -> ext::string
{
    // The 'text_content' getter returns the equivalent 'value' attribute value that is stored in the private class.
    // Apply custom element reactions to this setter.
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->value;
    _CE_REACTIONS_METHOD_EXE
}


auto dom::attr::set_node_value(ext::string new_node_value) -> ext::view_of_t<ext::string>
{
    // The 'node_value' setter sets the equivalent 'value' attribute value that is stored in the private class to the
    // 'new_node_value'. Apply custom element reactions to this setter.
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->value = std::move(new_node_value);
    _CE_REACTIONS_METHOD_EXE
}


auto dom::attr::set_text_content(ext::string new_text_content) -> ext::view_of_t<ext::string>
{
    // The 'text_content' setter sets the equivalent 'value' attribute value that is stored in the private class to the
    // 'new_text_content'. Apply custom element reactions to this getter.
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->value = std::move(new_text_content);
    _CE_REACTIONS_METHOD_EXE
}


auto dom::attr::get_namespace_uri() const -> ext::string
{
    // The 'namespace_uri' getter returns the equivalent 'namespace_' attribute value that is stored in the private
    // class.
    ACCESS_PIMPL;
    return d->namespace_;
}


auto dom::attr::get_prefix() const -> ext::string
{
    // The 'prefix' getter returns the equivalent 'namespace_prefix' attribute value that is stored in the private
    // class.
    ACCESS_PIMPL;
    return d->namespace_prefix;
}


auto dom::attr::get_local_name() const -> ext::string
{
    // The 'local_name' getter returns the equivalent 'local_name' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->local_name;
}


auto dom::attr::get_name() const -> ext::string
{
    // The 'name' getter returns the qualified name derived from this element, using a detail method.
    return detail::qualified_name(this);
}


auto dom::attr::get_value() const -> ext::string
{
    // The 'value' getter returns the equivalent 'value' attribute value that is stored in the private class. Apply
    // custom element reactions to this getter.
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->value;
    _CE_REACTIONS_METHOD_EXE
}


auto dom::attr::get_owner_element() const -> element*
{
    // The 'element' getter returns the equivalent 'element' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->element.get();
}


auto dom::attr::set_value(ext::string new_value) -> ext::view_of_t<ext::string>
{
    // The 'value' setter sets the equivalent 'value' attribute value that is stored in the private class to the
    // 'new_value'. Apply custom element reactions to this setter.
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        detail::set_existing_attribute_value(this, std::move(new_value));
        return d->value;
    _CE_REACTIONS_METHOD_EXE
}


auto dom::attr::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<node>()
        .property("namespaceURI", &attr::get_namespace_uri)
        .property("prefix", &attr::get_prefix)
        .property("localName", &attr::get_local_name)
        .property("name", &attr::get_name)
        .property("value", &attr::get_value, &attr::set_value)
        .property("ownerElement", &attr::get_owner_element)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
