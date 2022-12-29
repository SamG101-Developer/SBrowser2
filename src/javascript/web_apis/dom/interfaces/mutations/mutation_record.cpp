module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


module apis.dom.mutation_record;
import apis.dom.mutation_record_private;

import ext.core;
import js.env.module_type;


auto dom::mutation_record::get_type() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->type;
}


auto dom::mutation_record::get_attribute_name() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->attribute_name;
}


auto dom::mutation_record::get_attribute_namespace() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->attribute_namespace;
}


auto dom::mutation_record::get_old_value() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->old_value;
}


auto dom::mutation_record::get_target() const -> node*
{
    ACCESS_PIMPL;
    return d->target.get();
}


auto dom::mutation_record::get_previous_sibling() const -> node*
{
    ACCESS_PIMPL;
    return d->previous_sibling.get();
}


auto dom::mutation_record::get_next_sibling() const -> node*
{
    ACCESS_PIMPL;
    return d->next_sibling.get();
}


auto dom::mutation_record::get_added_nodes() const -> ext::vector_span<node*>
{
    ACCESS_PIMPL;
    return d->added_nodes;
}


auto dom::mutation_record::get_removed_nodes() const -> ext::vector_span<node*>
{
    ACCESS_PIMPL;
    return d->removed_nodes;
}


auto dom::mutation_record::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("type", &mutation_record::get_type)
        .property("attributeName", &mutation_record::get_attribute_name)
        .property("attributeNamespace", &mutation_record::get_attribute_namespace)
        .property("oldValue", &mutation_record::get_old_value)
        .property("target", &mutation_record::get_target)
        .property("previousSibling", &mutation_record::get_previous_sibling)
        .property("nextSibling", &mutation_record::get_next_sibling)
        .property("addedNodes", &mutation_record::get_added_nodes)
        .property("removedNodes", &mutation_record::get_removed_nodes)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
