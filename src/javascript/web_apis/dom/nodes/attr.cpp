#include "attr.hpp"
#include "attr_private.hpp"

#include "dom/detail/attribute_internals.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/nodes/element.hpp"


dom::nodes::attr::attr()
{
    INIT_PIMPL(attr);

    ACCESS_PIMPL(attr);
    d->element = nullptr;
}


auto dom::nodes::attr::get_node_value() const -> ext::string
{
    // The 'node_value' getter returns the equivalent 'value' attribute value that is stored in the private class. Apply
    // custom element reactions to this getter.
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const attr);
        return d->value;
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::attr::get_text_content() const -> ext::string
{
    // The 'text_content' getter returns the equivalent 'value' attribute value that is stored in the private class.
    // Apply custom element reactions to this setter.
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const attr);
        return d->value;
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::attr::set_node_value(ext::string new_node_value) -> ext::string
{
    // The 'node_value' setter sets the equivalent 'value' attribute value that is stored in the private class to the
    // 'new_node_value'. Apply custom element reactions to this setter.
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(attr);
        return d->value = std::move(new_node_value);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::attr::set_text_content(ext::string new_text_content) -> ext::string
{
    // The 'text_content' setter sets the equivalent 'value' attribute value that is stored in the private class to the
    // 'new_text_content'. Apply custom element reactions to this getter.
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(attr);
        return d->value = std::move(new_text_content);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::attr::get_namespace_uri() const -> ext::string
{
    // The 'namespace_uri' getter returns the equivalent 'namespace_' attribute value that is stored in the private
    // class.
    ACCESS_PIMPL(const attr);
    return d->namespace_;
}


auto dom::nodes::attr::get_prefix() const -> ext::string
{
    // The 'prefix' getter returns the equivalent 'namespace_prefix' attribute value that is stored in the private
    // class.
    ACCESS_PIMPL(const attr);
    return d->namespace_prefix;
}


auto dom::nodes::attr::get_local_name() const -> ext::string
{
    // The 'local_name' getter returns the equivalent 'local_name' attribute value that is stored in the private class.
    ACCESS_PIMPL(const attr);
    return d->local_name;
}


auto dom::nodes::attr::get_name() const -> ext::string
{
    // The 'name' getter returns the qualified name derived from this element, using a detail method.
    return detail::qualified_name(this);
}


auto dom::nodes::attr::get_value() const -> ext::string
{
    // The 'value' getter returns the equivalent 'value' attribute value that is stored in the private class. Apply
    // custom element reactions to this getter.
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const attr);
        return d->value;
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::attr::get_owner_element() const -> element*
{
    // The 'element' getter returns the equivalent 'element' attribute value that is stored in the private class.
    ACCESS_PIMPL(const attr);
    return d->element;
}


auto dom::nodes::attr::set_value(ext::string new_value) -> ext::string
{
    // The 'value' setter sets the equivalent 'value' attribute value that is stored in the private class to the
    // 'new_value'. Apply custom element reactions to this setter.
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const attr);
        detail::set_existing_attribute_value(this, std::move(new_value));
        return d->value;
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::attr::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
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
