module;
#include <function2/function2.hpp>

export module apis.dom.detail;
import apis.dom.types;
import ext.functional;
import ext.string;

namespace dom {class dom_exception;}
namespace js::env {class env;}


export namespace
{
    template <v8_primitive_error_t T>
    auto throw_v8_exception(
            ext::unique_function<auto() -> bool>&& condition,
            ext::u8string&& message,
            js::env::env& e)
            -> void;

    template <dom_exception_error_t T>
    auto throw_v8_exception(
            ext::unique_function<auto() -> bool>&& condition,
            ext::u8string&& message,
            js::env::env& e)
            -> void;

    auto throw_v8_exception(dom::dom_exception&& exception)
            -> void;
}
