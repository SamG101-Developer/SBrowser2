#include "type_mapping_internals.hpp"

#include <v8-internal.h>
#include <v8-isolate.h>
#include <v8-object.h>


template <typename T>
auto web_idl::detail::create_promise(v8::Local<v8::Context> realm) -> ext::promise <T>
{
    auto promise = v8::Promise::New(realm->GetIsolate());
    return convert<ext::promise<T>>(promise);
}


template <typename T>
web_idl::
