#include "abstract_operations.hpp"

#include "ext/hashing.ixx"
#include "ext/regex.ixx"
#include "ext/tuple.ixx"
#include "ext/type_traits.ixx"
#include "ext/variadic.ixx"

#include "javascript/environment/realms.hpp"

#include <range/v3/view/take.hpp>
#include <range/v3/view/drop.hpp>

#include <v8-isolate.h>
#include <v8-object.h>


template <ext::type_is_enum E, typename ...Args>
auto console::detail::logger(E log_level, Args&& ...args) -> void
{
    constexpr_return_if (sizeof...(args) == 0);

    sizeof...(args) == 1
            ? printer(log_level, ext::nth_variadic_value<0>(std::forward<Args>(args)...))
            : printer(log_level, std::forward<Args>(args)...);
}


template <typename ...Args>
auto console::detail::formatter(Args&& ...args) -> ext::string
{
    return_if (sizeof...(args) == 1) ext::nth_variadic_value<0>(std::forward<Args>(args)...);
    ext::string    target  = ext::nth_variadic_value<0>(std::forward<Args>(args)...);
    decltype(auto) current = ext::nth_variadic_value<1>(std::forward<Args>(args)...);

    auto e = js::env::env::current();

    auto format_specifier = ext::regex::StringPiece{};
    ext::regex_utils::PartialMatch(target, "(%[s|d|i])", &format_specifier);
    return_if (format_specifier.empty()) {};

    auto converted = ext::string{};
    string_switch (format_specifier)
    {
        string_case(u8"%s"):
            converted = std::move(current);
            break;

        string_case(u8"%d"):
        string_case(u8"%i"):
            converted = v8pp::to_v8(e.js.agent(), current).IsSymbol() ? "NaN" : ext::to_string(current);
            break;

        string_case(u8"%f"):
            converted = v8pp::to_v8(e.js.agent(), current).IsSymbol() ? "NaN" : ext::to_string(current);
            break;

        string_case(u8"%o"):
            // TODO

        string_case(u8"%O"):
            // TODO

        string_case(u8"%c"):
            // TODO

        string_default:
            ;
    }

    if (!converted.empty())
        target |= ranges::views::replace(format_specifier.data(), std::move(converted));

    auto result = ext::nth_variadic_values<3>(std::forward<Args>(args)...);
    ext::apply(BIND_FRONT(formatter, std::move(target)), std::move(result));
}