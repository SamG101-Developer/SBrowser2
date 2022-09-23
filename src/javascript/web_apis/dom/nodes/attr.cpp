#include "attr.hpp"

#include "dom/detail/attribute_internals.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/nodes/element.hpp"


dom::nodes::attr::attr() : INIT_PIMPL
{}


auto dom::nodes::attr::get_name() const -> ext::string
{return detail::qualified_name(this);}


auto dom::nodes::attr::get_value() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        return d_ptr->value;
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::attr::set_value(ext::string new_value) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        detail::set_existing_attribute_value(this, std::move(new_value));
        return d_ptr->value;
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::attr::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<attr>{isolate}
        .inherit<node>()
        .property("namespaceURI", &attr::get_namespace_uri)
        .property("prefix", &attr::get_prefix)
        .property("localName", &attr::get_local_name)
        .property("name", &attr::get_name)
        .property("value", &attr::get_value, &attr::set_value)
        .property("ownerElement", &attr::get_owner_element)
        .auto_wrap_objects();

    return std::move(conversion);
}
