#ifndef SBROWSER2_SRC_JAVASCRIPT_MACROS_EXPOSE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_MACROS_EXPOSE_HPP

#include "ext/macros.hpp"

#include <tuplet/tuple.hpp>
#include <v8-isolate.h>
#include <v8pp/class.hpp>
#include <v8pp/convert.hpp>


// Shorthand macro to get the current isolate and current and save them into local variables, to avoid having to make
// multiple calls to the same two methods. Also avoid having to use Google-style code in non-Google-style code in the
// rest of the code base.
#define ISOLATE_AND_CONTEXT                             \
    decltype(auto) isolate = v8::Isolate::GetCurrent(); \
    auto context = isolate->GetCurrentContext();


// A failed conversion into V8 (ie environment mismatch etc) returns a tuple containing the creation flag set to false,
// and an empty v8pp::class_ object which acts as a placeholder.
#define V8_INTEROP_FAILED_CONVERSION ext::make_tuple(false, v8pp::class_<this_t>{nullptr})
#define V8_INTEROP_SUCCESSFUL_CONVERSION ext::make_tuple(true, std::move(v8_conversion))


// A successful conversion into V8 returns a tuple containing the creation flag set to true, and the conversion to a
// v8pp::class_ object, with its properties, methods, constructors etc all added.
#define V8_INTEROP_CREATE_JS_OBJECT                                           \
    return_if (~(E & _allowed_v8_environments)) V8_INTEROP_FAILED_CONVERSION; \
    decltype(auto) v8_conversion = v8pp::class_<this_t>{isolate}


// Extend an existing V8 conversion with more properties and methods etc, used when objects have certain extra members
// based on their environment type / if the environment is secure (methods especially0.
#define V8_INTEROP_EXTEND_JS_OBJECT(...) \
    if (~(E & __VA_ARGS__)) v8_conversion


// Used in the definition of a class, to bind the allowed V8 environment types to the class, followed by the static
// method that returns the V8 conversion (same for each class due to the this_t type being available to every V8
// convertible class).
#define MAKE_V8_AVAILABLE(A)                                      \
    using enum js::env::module_t;                                 \
    inline static js::env::module_t _allowed_v8_environments = A; \
    static auto _to_v8(js::env::module_t E, v8::Isolate* isolate) -> ext::tuple<bool, v8pp::class_<this_t>>


#endif //SBROWSER2_SRC_JAVASCRIPT_MACROS_EXPOSE_HPP
