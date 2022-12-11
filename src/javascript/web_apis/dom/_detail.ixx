module;
#include <function2/function2.hpp>

export module apis.dom.detail;
import apis.dom.types;
import ext.any;
import ext.boolean;
import ext.functional;
import ext.map;
import ext.string;
import ext.vector;

namespace dom {class dom_exception;}
namespace js::env {class env;}


export namespace dom::detail
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

    auto flatten_more(
            const ext::map<ext::string, ext::any>& options)
            -> ext::map<ext::string, ext::any>;

    auto flatten_more(
            ext::boolean options)
            -> ext::map<ext::string, ext::any>;

    auto flatten(
            event_listener_options_t&& options)
            -> ext::boolean;
}
