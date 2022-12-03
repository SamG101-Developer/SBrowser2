#include "exception_internals.hpp"


#include "javascript/environment/realms.hpp"

#include "dom/_typedefs.hpp"
#include "dom/other/dom_exception.hpp"

#include <range/v3/algorithm/fold_left.hpp>
#include <v8-exception.h>
#include <v8-value.h>
#include <v8pp/convert.hpp>


template <v8_primitive_error_t T>
auto dom::detail::throw_v8_exception(
        ext::unique_function<auto() -> bool>&& condition,
        ext::u8string&& message,
        js::env::env& e)
        -> void
{
    return_if (condition());
    
    using enum v8_primitive_error_t;
    auto exception = v8::Exception::Error(v8pp::to_v8(e.js.agent(), message));

    switch(T)
    {
        case V8_TYPE_ERROR:
            exception = v8::Exception::TypeError(v8pp::to_v8(e.js.agent(), message));
            break;

        case V8_RANGE_ERROR:
            exception = v8::Exception::RangeError(v8pp::to_v8(e.js.agent(), message));
            break;

        case V8_REFERENCE_ERROR:
            exception = v8::Exception::ReferenceError(v8pp::to_v8(e.js.agent(), message));
            break;

        case V8_SYNTAX_ERROR:
            exception = v8::Exception::SyntaxError(v8pp::to_v8(e.js.agent(), message));
            break;

        case V8_WASM_COMPILE_ERROR:
            exception = v8::Exception::WasmCompileError(v8pp::to_v8(e.js.agent(), message));
            break;

        case V8_WASM_LINK_ERROR:
            exception = v8::Exception::WasmLinkError(v8pp::to_v8(e.js.agent(), message));
            break;

        case V8_WASM_RUNTIME_ERROR:
            exception = v8::Exception::WasmRuntimeError(v8pp::to_v8(e.js.agent(), message));
            break;

        default:
            exception = v8::Exception::Error(v8pp::to_v8(e.js.agent(), message));
            break;
    }

    e.js.agent()->ThrowException(exception);
}


template <dom::detail::dom_exception_error_t T>
auto dom::detail::throw_v8_exception(
        ext::unique_function<auto() -> bool>&& condition,
        ext::u8string&& message,
        js::env::env& e)
        -> void
{
    return_if (!condition());
    
    auto exception = v8pp::to_v8(e.js.agent(), dom::other::dom_exception{std::move(message), T});
    e.js.agent()->ThrowException(exception);
}