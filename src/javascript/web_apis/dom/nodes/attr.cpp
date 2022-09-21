#include "attr.hpp"

#include "dom/detail/attribute_internals.hpp"
#include "dom/nodes/element.hpp"


dom::nodes::attr::attr()
        : INIT_PIMPL
{
    bind_get(node_value);
    bind_get(text_content);

    bind_set(node_value);
    bind_set(text_content);
    bind_set(value);
}


auto dom::nodes::attr::set_value(
        const ext::string& val)
        -> void
{
    // overwrite the current value in this attribute class with the new value
    detail::set_existing_attribute_value(this, val);
}


auto dom::nodes::attr::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<attr>{isolate}
            .inherit<node>()
            .var("namespaceURI", &attr::namespace_uri, true)
            .var("prefix", &attr::prefix, true)
            .var("localName", &attr::local_name, true)
            .var("name", &attr::name, true)
            .var("value", &attr::value, false)
            .var("ownerElement", &attr::owner_element, true);

    return std::move(conversion);
}
