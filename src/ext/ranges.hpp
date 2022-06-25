#ifndef SBROWSER2_RANGES_HPP
#define SBROWSER2_RANGES_HPP

#include <ext/string.hpp>
#include <ext/type_traits.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/transform.hpp>



// additional functionality to ranges v3
template <iterable Rng, typename _ViewFn> // TODO : remove this template for a inlined concept
auto operator|=(Rng& _Container, ranges::views::view_closure<_ViewFn> _ViewFunction)
{
    _Container = _Container | _ViewFunction | ranges::to<Rng>();
    return _Container;
}


namespace ranges::views {auto split_string(::ext::string_view delimiter) -> range_v3_view auto;}

auto ranges::views::split_string(::ext::string_view delimiter) -> range_v3_view auto
{
    return ranges::views::split(delimiter)
            | ranges::views::transform([](range_v3_view auto&& sub_range) {return sub_range | ranges::to<::ext::string>();});
}


#endif //SBROWSER2_RANGES_HPP
