#ifndef SBROWSER2_JAVASCRIPT_WEB_APIS_INDEXED_DB__TYPEDEFS_HPP
#define SBROWSER2_JAVASCRIPT_WEB_APIS_INDEXED_DB__TYPEDEFS_HPP


#include <bit>
#include <variant>
#include "ext/any.hpp"
#include "ext/date.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"

namespace indexed_db::detail
{
    using number_key_t = ext::number<double>;
    using date_key_t = ext::datetime;
    using string_key_t = ext::string;
    using binary_key_t = std::byte;
    using array_key_t = ext::vector<ext::any>;
    using any_key_t = ext::variant<date_key_t, string_key_t, binary_key_t, array_key_t>; // number_key_t causes untold clangd crashes for unknown reasons

    template <typename T>
    struct record_value {using type = void;};

    template <>
    struct record_value<number_key_t> {using type = ext::number<double>;};

    template <>
    struct record_value<date_key_t> {using type = ext::number<double>;};

    template <>
    struct record_value<string_key_t> {using type = ext::string;};

    template <>
    struct record_value<binary_key_t> {using type = ext::string;};

    template <>
    struct record_value<array_key_t> {using type = ext::vector<ext::any>;};

    template <typename T>
    using record_value_t = typename record_value<T>::type;

    enum class transaction_mode_t {READONLY, READ_WRITE, VERSION_CHANGE};
    enum class transaction_state_t {ACTIVE, INACTIVE, COMMITTING, FINISHED};
    enum class durability_hint_t {STRICT, RELAXED, DEFAULT};
    enum class cursor_direction_t {NEXT, NEXT_UNIQUE, PREV, PREV_UNIQUE};
}

#endif //SBROWSER2_JAVASCRIPT_WEB_APIS_INDEXED_DB__TYPEDEFS_HPP
