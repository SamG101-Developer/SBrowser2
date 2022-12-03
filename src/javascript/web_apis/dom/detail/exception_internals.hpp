#ifndef SBROWSER2_EXCEPTION_INTERNALS_HPP
#define SBROWSER2_EXCEPTION_INTERNALS_HPP

#include "ext/casting.ixx"

#include "ext/string.hpp"
#include "ext/tuple.ixx"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(dom)
namespace dom::other {class dom_exception;}
namespace js::env {class env;}

// #define NO_CONDITION [] -> bool {return true;}
// #define P(key, val) tuplet::pair{key, val}


namespace dom::detail
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

    auto throw_v8_exception(dom::other::dom_exception&& exception)
            -> void;
}


#endif //SBROWSER2_EXCEPTION_INTERNALS_HPP
