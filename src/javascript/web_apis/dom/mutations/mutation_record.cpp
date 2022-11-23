#include "mutation_record.hpp"
#include "dom_object.hpp"
#include "mutation_record_private.hpp"


auto dom::mutations::mutation_record::get_type() const -> ext::string_view
{
    ACCESS_PIMPL(const mutation_record);
    return d->type;
}


auto dom::mutations::mutation_record::get_attribute_name() const -> ext::string_view
{
    ACCESS_PIMPL(const mutation_record);
    return d->attribute_name;
}


auto dom::mutations::mutation_record::get_attribute_namespace() const -> ext::string_view
{
    ACCESS_PIMPL(const mutation_record);
    return d->attribute_namespace;
}


auto dom::mutations::mutation_record::get_old_value() const -> ext::string_view
{
    ACCESS_PIMPL(const mutation_record);
    return d->old_value;
}


auto dom::mutations::mutation_record::get_target() const -> nodes::node*
{
    ACCESS_PIMPL(const mutation_record);
    return d->target;
}


auto dom::mutations::mutation_record::get_previous_sibling() const -> nodes::node*
{
    ACCESS_PIMPL(const mutation_record);
    return d->previous_sibling;
}


auto dom::mutations::mutation_record::get_next_sibling() const -> nodes::node*
{
    ACCESS_PIMPL(const mutation_record);
    return d->next_sibling;
}


auto dom::mutations::mutation_record::get_added_nodes() const -> ext::vector_span<nodes::node*>
{
    ACCESS_PIMPL(const mutation_record);
    return d->added_nodes;
}


auto dom::mutations::mutation_record::get_removed_nodes() const -> ext::vector_span<nodes::node*>
{
    ACCESS_PIMPL(const mutation_record);
    return d->removed_nodes;
}


auto dom::mutations::mutation_record::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
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
