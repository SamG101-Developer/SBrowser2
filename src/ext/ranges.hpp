#ifndef SBROWSER2_RANGES_HPP
#define SBROWSER2_RANGES_HPP

#include <ext/string.hpp>
#include <ext/type_traits.hpp>

#include <range/v3/range/conversion.hpp>
#include <range/v3/action/transform.hpp>
#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/drop_while.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/remove.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/take_while.hpp>
#include <range/v3/view/transform.hpp>

namespace ranges::views {struct lowercase_fn;}
namespace ranges::views {struct uppercase_fn;}
namespace ranges::views {struct split_string_fn;}
namespace ranges::views {struct take_until_fn;}
namespace ranges::views {struct drop_until_fn;}
namespace ranges::views {template <typename _Tx> struct cast_all_to_fn;}

namespace ranges::actions {struct lowercase_fn;}
namespace ranges::actions {struct uppercase_fn;}

namespace ranges {struct contains_all_fn;}
namespace ranges {struct first_where_fn;}
namespace ranges {struct last_where_fn;}


/* VIEWS */
struct ranges::views::lowercase_fn
{
    constexpr auto operator()() const
    {
        return ranges::views::transform([](char c) {return std::tolower(c);});
    }
};


struct ranges::views::uppercase_fn
{
    constexpr auto operator()() const
    {
        return ranges::views::transform([](char c) {return std::toupper(c);});
    }
};


struct ranges::views::split_string_fn
{
    constexpr auto operator()(char delimiter) const
    {
        return ranges::views::split(delimiter) | ranges::views::transform([](range_v3_view auto&& sub_range) {return sub_range | ranges::to<::ext::string>();});
    }
};


struct ranges::views::take_until_fn
{
    template <typename _Fx>
    constexpr auto operator()(_Fx&& _Pred) const
    {
        return ranges::views::take_while([_Pred = std::forward<_Fx>(_Pred)](auto&& _Elem) {return !_Pred(std::forward<decltype(_Elem)>(_Elem));});
    }
};


struct ranges::views::drop_until_fn
{
    template <typename _Fx>
    constexpr auto operator()(_Fx&& _Pred) const
    {
        return ranges::views::drop_while([_Pred = std::forward<_Fx>(_Pred)](auto&& _Elem) {return !_Pred(std::forward<decltype(_Elem)>(_Elem));});
    }
};


template <typename _Tx>
struct ranges::views::cast_all_to_fn
{
    constexpr auto operator()(::ext::boolean remove_nullptr = true) const // TODO : apply parameter
    {
        return ranges::views::transform([](auto* pointer) {return dynamic_cast<_Tx*>(pointer);}) | ranges::views::remove(nullptr);
    }
};


/* ACTIONS */
struct ranges::actions::lowercase_fn
{
    constexpr auto operator()() const
    {
        return ranges::actions::transform([](char c) {return std::tolower(c);});
    }
};


struct ranges::actions::uppercase_fn
{
    constexpr auto operator()() const
    {
        return ranges::actions::transform([](char c) {return std::toupper(c);});
    }
};


/* ALGORITHMS */
struct ranges::contains_all_fn
{
    template <typename Rng1, typename Rng2>
    constexpr auto operator()(Rng1&& range1, Rng2&& range2) const
    {
        return ranges::all_of(range2, [range1](auto&& item_2) {ranges::contains(std::forward<Rng1>(range1), std::forward<Rng2>(item_2));});
    }
};


struct ranges::first_where_fn
{
    template <typename Rng1, typename Fx>
    constexpr auto operator()(Rng1&& range1, Fx&& function) const
    {
        auto filtered = range1 | ranges::views::filter(std::forward<Fx>(function));
        return filtered.front();
    }
};


struct ranges::last_where_fn
{
    template <typename Rng1, typename Fx>
    constexpr auto operator()(Rng1&& range1, Fx&& function) const
    {
        auto filtered = range1 | ranges::views::filter(std::forward<Fx>(function));
        return filtered.back();
    }
};


namespace ranges::views {constexpr split_string_fn split_string;}
namespace ranges::views {constexpr lowercase_fn lowercase;}
namespace ranges::views {constexpr uppercase_fn uppercase;}
namespace ranges::views {constexpr take_until_fn take_until;}
namespace ranges::views {constexpr drop_until_fn drop_until;}
namespace ranges::views {template <typename _Tx> constexpr cast_all_to_fn<_Tx> cast_all_to;}
namespace ranges::actions {constexpr lowercase_fn lowercase;}
namespace ranges::actions {constexpr uppercase_fn uppercase;}
namespace ranges {constexpr contains_all_fn contains_all;}
namespace ranges {constexpr first_where_fn first_where;}
namespace ranges {constexpr last_where_fn last_where;}


#endif //SBROWSER2_RANGES_HPP
