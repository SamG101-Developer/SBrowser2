#ifndef SBROWSER2_SRC_EXT_VIEW_HPP
#define SBROWSER2_SRC_EXT_VIEW_HPP

#include "ext/casting.hpp"
#include "ext/concepts.hpp"
#include "range/v3/range_fwd.hpp"

#include <initializer_list>
#include <iterator>
#include <span>

#include <range/v3/iterator/operations.hpp>
#include <range/v3/iterator/reverse_iterator.hpp>


_EXT_BEGIN

template <typename T, typename BeginIter, typename EndIter = BeginIter>
class view final
{
public aliases:
    using element_type = T;
    using value_type = std::remove_cv_t<element_type>;

    using begin_iterator = BeginIter;
    using reverse_begin_iterator = ranges::reverse_iterator<begin_iterator>;
    using end_iterator = EndIter;
    using reverse_end_iterator = ranges::reverse_iterator<end_iterator>;
    using pointer = std::remove_pointer_t<T>*;
    using reference = std::remove_reference_t<T>&;
    using const_pointer = const pointer;
    using const_reference = const reference;
    using difference_type = ptrdiff_t;
    using size_type = size_t;

public constructors:
    view()
            : fixed_begin{nullptr}
            , fixed_end{nullptr}
            , fixed_size{0}
    {};

    view(begin_iterator begin, end_iterator end)
            : fixed_begin{begin}
            , fixed_end{end}
            , fixed_size{ranges::distance(begin, end)}
    {}

    view(begin_iterator begin, size_type size)
            : fixed_begin{begin}
            , fixed_end{ranges::next(begin, size)}
            , fixed_size{size}
    {}

    view(view&& other) noexcept
            : fixed_begin{std::make_move_iterator(std::move(other.begin()))}
            , fixed_end{std::make_move_iterator(std::move(other.end()))}
            , fixed_size{std::move(other.size())}
    {}

    template <iterable Container> requires (!inherit<Container, view>)
    view(Container&& other)
            : fixed_begin{ranges::begin(other)}
            , fixed_end{ranges::end(other)}
            , fixed_size{ranges::size(other)}
    {}

    view(const view&) = delete;
    auto operator=(const view&) = delete;
    auto operator=(view&&) noexcept = delete;

public cpp_operators:
    template <typename Container>
    auto operator==(Container&& other) const -> bool {return data() == other.data();}

    template <typename Container>
    auto operator<=>(Container other) const {return data() <=> other.data();}

public cpp_members:
    auto data() {return fixed_begin;}
    auto empty() {return fixed_size == 0;}
    auto size() {return fixed_size;}

    auto begin() {return fixed_begin;}
    auto rbegin() {return ranges::reverse_iterator<BeginIter>{fixed_begin};}
    auto front() {return *fixed_begin;}

    auto end() {return fixed_end;}
    auto rend() {return ranges::reverse_iterator<EndIter>{fixed_end};}
    auto back() {return *fixed_end;}

    auto first(size_type count) {return view{fixed_begin, count};}
    auto last(size_type count) {return view{ranges::prev(fixed_end, count), count};}
    auto subspan() {return view{fixed_begin, fixed_end};}
    auto subspan(size_type offset, size_type count) {return view{ranges::next(fixed_begin, offset), count};}

    auto at(size_type where) -> element_type {return *ranges::next(fixed_begin, where);}

private:
    const BeginIter fixed_begin;
    const EndIter fixed_end;
    const size_type fixed_size;
};


_EXT_END

#endif //SBROWSER2_SRC_EXT_VIEW_HPP
