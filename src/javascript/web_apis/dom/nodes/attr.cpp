#include "attr.hpp"

#include "dom/detail/attribute_internals.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/nodes/element.hpp"


dom::nodes::attr::attr()
{
    INIT_PIMPL(attr);
}


auto dom::nodes::attr::get_node_value() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const attr);
        return d->value;
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::attr::get_text_content() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const attr);
        return d->value;
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::attr::set_node_value(ext::string new_node_value) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(attr);
        d->value = new_node_value;
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::attr::set_text_content(ext::string new_text_content) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(attr);
        d->value = new_text_content;
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::attr::get_namespace_uri() const -> ext::string
{
    ACCESS_PIMPL(const attr);
    return d->namespace_;
}


auto dom::nodes::attr::get_prefix() const -> ext::string
{
    ACCESS_PIMPL(const attr);
    return d->namespace_prefix;
}


auto dom::nodes::attr::get_local_name() const -> ext::string
{
    ACCESS_PIMPL(const attr);
    return d->local_name;
}


auto dom::nodes::attr::get_name() const -> ext::string
{
    return detail::qualified_name(this);
}


auto dom::nodes::attr::get_value() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const attr);
        return d->value;
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::attr::get_owner_element() const -> element*
{
    ACCESS_PIMPL(const attr);
    return d->element;
}


auto dom::nodes::attr::set_value(ext::string new_value) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const attr);
        detail::set_existing_attribute_value(this, std::move(new_value));
        return d->value;
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
