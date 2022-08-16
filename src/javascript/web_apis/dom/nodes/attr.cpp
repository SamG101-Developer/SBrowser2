#include "attr.hpp"

#include "dom/detail/attribute_internals.hpp"


dom::nodes::attr::attr()
{
    bind_get(node_value);
    bind_get(text_content);
    bind_set(node_value);
    bind_set(text_content);
    bind_set(value);
}


auto dom::nodes::attr::set_value(
        ext::string_view val)
        -> void
{
    // overwrite the current value in this attribute class with the new value
    detail::set_existing_attribute_value(this, val);
}


auto dom::nodes::attr::qualified_name()
        const -> ext::string
{
    ext::string concat = prefix() + ":" + local_name();
    return concat;
}


auto dom::nodes::attr::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<attr>{isolate}
            .inherit<node>()
            .var("namespaceURI", &attr::namespace_uri, true)
            .var("prefix", &attr::prefix, true)
            .var("localName", &attr::local_name, true)
            .var("name", &attr::name, true)
            .var("value", &attr::value, false)
            .var("ownerElement", &attr::owner_element, true);
}
