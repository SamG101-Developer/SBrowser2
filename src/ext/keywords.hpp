#pragma once
#ifndef SBROWSER2_KEYWORDS_HPP
#define SBROWSER2_KEYWORDS_HPP

#define _EXT ::ext::
#define _EXT_BEGIN namespace ext {
#define _EXT_END } // namespace ext
#define _EXT_DETAIL_BEGIN namespace ext::detail {
#define _EXT_DETAIL_END } // namespace ext::detail
#define _EXT_SHORTHAND_BEGIN namespace ext::shorthand {
#define _EXT_SHORTHAND_END } // namespace ext::shorthand
#define _EXT_LITERALS_BEGIN namespace ext::literals {
#define _EXT_LITERALS_END }

#define COMMA ,

#define STRINGIFY(x) #x
#define EXPAND(x) x
#define STRINGIFY_MACRO(x) STRINGIFY(x)
#define CONCAT(n1, n2) STRINGIFY_MACRO(EXPAND(n1)EXPAND(n2))

#define USE_INNER_TYPES(api) CONCAT(api, /_typedefs.hpp)
#define USE_CONCEPTS(api) CONCAT(api, /_concepts.hpp)

#define catch_all catch (...)
#define catch_specific(exception_t) catch(const exception_t& exception)
#define catch_other catch (...)

#define string_switch(_String) switch(ext::hash{}(_String))
#define string_case(_String) case(ext::hash{}(_String))
#define string_default default

#define friends
#define aliases
#define enums
#define constructors

#define js_static_constants
#define js_methods
#define js_properties
#define js_slot_methods
#define js_slots

#define cpp_static_methods
#define cpp_methods
#define cpp_properties
#define cpp_accessors
#define cpp_operators
#define cpp_nested_classes

#define return_if(condition) if (condition) return
#define break_if(condition) if (condition) break
#define continue_if(condition) if (condition) continue
#define for_if(if_statement, for_statement) if (if_statement) for (for_statement)

#define constexpr_return_if(condition) if constexpr(condition) return

#define _EXT_NODISCARD [[nodiscard]]
#define _EXT_FALLTHOUGH [[fallthrough]]

#define DISALLOW_COPY(type)     \
    type(const type&) = delete; \
    auto operator=(const type&) -> type& = delete

#define ALLOW_COPY(type)               \
    type(const type&) = default; \
    auto operator=(const type&) -> type& = default

#define ALLOW_MOVE(type)             \
    type(type&&) noexcept = default; \
    auto operator=(type&&) noexcept -> type& = delete


#endif //SBROWSER2_KEYWORDS_HPP
