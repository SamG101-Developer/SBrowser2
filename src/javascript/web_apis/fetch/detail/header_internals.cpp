#include "header_internals.hpp"






#include "infra/detail/infra_strings_internals.hpp"
#include "fetch/detail/http_internals.hpp"

#include <range/v3/to_container.hpp>
#include <range/v3/action/remove_if.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/sort.hpp>
#include <range/v3/range/operations.hpp>
#include <range/v3/view/drop_while.hpp>

#include <range/v3/view/iota.hpp>

#include <range/v3/view/reverse.hpp>
#include <range/v3/view/transform.hpp>



























template <ext::string_like T>
auto fetch::detail::normalize(T& potential_value) -> T&
{
    return infra::detail::strip_leading_and_trailing_ascii_whitespace(potential_value);
}
