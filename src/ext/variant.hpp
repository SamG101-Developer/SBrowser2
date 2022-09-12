#ifndef SBROWSER2_SRC_EXT_VARIANT_HPP
#define SBROWSER2_SRC_EXT_VARIANT_HPP

#include "ext/vector.hpp"
#include "ext/tuple.hpp"
#include <swl/variant.hpp>

#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>


_EXT_BEGIN

using namespace swl;


using variant_monostate_t = swl::monostate;


template <typename T>
const std::type_info& variant_type(T&& variant_object)
{
    return ext::visit([](auto&& _) -> decltype(auto) {return typeid(_);}, std::forward<T>(variant_object));
}



template <typename ...Types>
struct variant_to_tuple
{using type = void;};

template <typename ...Types>
struct variant_to_tuple<_EXT variant<Types...>>
{using type = _EXT tuple<Types...>;};

template <typename T>
using variant_to_tuple_t = typename variant_to_tuple<T>::type;


template <typename var_t, typename ret_t, typename F>
auto variant_transform(F&& function) -> ret_t
{
    using tuple_transform = variant_to_tuple_t<var_t>;
    ext::vector<std::optional<ret_t>> output_candidates;
    tuple_foreach(tuple_transform{}, std::forward<F>(function), output_candidates);

    return ranges::begin(output_candidates
            | ranges::views::filter(&decltype(output_candidates)::value_type::has_value)
            | ranges::views::transform(std::mem_fn(&decltype(output_candidates)::value_type::value)));
}


_EXT_END


#endif //SBROWSER2_SRC_EXT_VARIANT_HPP
