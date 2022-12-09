module;
#include "ext/macros/pimpl.hpp"


module apis.dom.document_type;


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
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<node>()
        .inherit<mixins::child_node>()
        .property("name", &document_type::get_name)
        .property("publicId", &document_type::get_public_id)
        .property("systemId", &document_type::get_system_id)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
