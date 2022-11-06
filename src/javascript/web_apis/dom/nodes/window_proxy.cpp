#include "window_proxy.hpp"
#include "window_proxy_private.hpp"

#include "ext/casting.hpp"

#include "ecma/spec_262/10_ordinary_and_exotic_objects_behaviours/10_4_builtin_methods_and_slots.hpp"

#include <v8-object.h>


auto dom::nodes::window_proxy::GetPrototype() -> v8::Local<v8::Value>
{
    ACCESS_PIMPL(const window_proxy);
    return html::detail::is_platform_object_same_origin(d->Window())
            ? d->Window()->GetPrototype()
            : v8::Null(d->Window()->GetIsolate());
}


auto dom::nodes::window_proxy::SetPrototype(
        v8::Local<v8::Context> context,
        v8::Local<v8::Value> prototype)
        -> v8::Maybe<bool>
{
    js::ecma::SetImmutablePrototype(*this, prototype);
}


auto dom::nodes::window_proxy::IsExtensible() -> bool
{
    return true;
}


auto dom::nodes::window_proxy::PreventExtensions() -> bool
{
    return false;
}


auto dom::nodes::window_proxy::GetOwnPropertyDescriptor(
        v8::Local<v8::Context> context,
        v8::Local<v8::Name> key)
        -> v8::MaybeLocal<v8::Value>
{
    ACCESS_PIMPL(const window_proxy);

    auto value = ext::nullptr_cast<window_proxy*>();

    if (web_idl::detail::is_array_index_property_name(key))
    {
        decltype(auto) index = key.As<v8::Number>()->Value();
        decltype(auto) children = detail::document_tree_child_navigables(d->window->d_func()->document.get());

        // TODO
    }
}
