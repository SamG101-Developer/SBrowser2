#ifndef SBROWSER2_EXCEPTION_INTERNALS_HPP
#define SBROWSER2_EXCEPTION_INTERNALS_HPP

#include "ext/casting.hpp"
#include "ext/functional.hpp"
#include "ext/string.hpp"
#include "ext/tuple.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(dom)

#define NO_CONDITION [] -> bool {return true;}
#define P(key, val) tuplet::pair{key, val}


namespace dom::detail
{
    template <v8_primitive_error_t exception_type>
    auto throw_v8_exception(
            exception_condiditional_t&& condition = NO_CONDITION,
            ext::string_view exception_message = u8"")
            -> void;

    template <dom_exception_error_t exception_type, typename ...T>
    auto throw_v8_exception(
            exception_condiditional_t&& condition = NO_CONDITION,
            ext::string_view description = u8"",
            ext::vector<ext::string>&& possible_causes = {},
            ext::vector<ext::string>&& possible_fixes = {},
            T&&... object_information)
            -> void;
}


#endif //SBROWSER2_EXCEPTION_INTERNALS_HPP
