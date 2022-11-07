#include "abstract_operations.hpp"

#include "ext/tuple.hpp"
#include "ext/type_traits.hpp"
#include "ext/variadic.hpp"

#include <range/v3/view/take.hpp>
#include <range/v3/view/drop.hpp>


template <typename ...Args>
auto console::detail::logger(detail::log_level_t log_level, Args&& ...args) -> void
{
    constexpr_return_if (sizeof...(args) == 0);

    sizeof...(args) == 1
            ? printer(log_level, ext::nth_variadic_value<0>(std::forward<Args>(args)...))
            : printer(log_level, std::forward<Args>(args)...);
}
