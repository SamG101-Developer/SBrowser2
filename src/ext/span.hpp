#ifndef SBROWSER2_SRC_EXT_SPAN_HPP
#define SBROWSER2_SRC_EXT_SPAN_HPP

#include "ext/casting.hpp"
#include "ext/concepts.hpp"
#include "ext/array.hpp"
#include "ext/map.hpp"
#include "ext/queue.hpp"
#include "ext/set.hpp"
#include "ext/stack.hpp"
#include "ext/vector.hpp"

#include <initializer_list>
#include <iterator>
#include <span>

#include <range/v3/range_fwd.hpp>
#include <range/v3/iterator/operations.hpp>
#include <range/v3/iterator/reverse_iterator.hpp>


_EXT_BEGIN

template <typename T, typename BeginIter, typename EndIter>
class span final
{
public aliases:
    using element_type = T;
    using value_type = std::remove_cv_t<element_type>;

    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    using begin_iterator = BeginIter;
    using reverse_begin_iterator = ranges::reverse_iterator<begin_iterator>;
    using end_iterator = EndIter;
    using reverse_end_iterator = ranges::reverse_iterator<end_iterator>;

    // These two type definitions aren't used by the class, but are required to make Ranges-V3 recognise the class as a
    // view closure, such that it can be used for filters and transforms etc.
    using iterator = begin_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;

public constructors:
    span()
            : fixed_begin{nullptr}
            , fixed_end{nullptr}
            , fixed_size{0}
    {};

    span(const begin_iterator begin, const end_iterator end)
            : fixed_begin{begin}
            , fixed_end{end}
            , fixed_size{std::bit_cast<size_t>(ranges::distance(begin, end))}
    {}

    span(const begin_iterator begin, size_type size)
            : fixed_begin{begin}
            , fixed_end{ranges::next(begin, size)}
            , fixed_size{size}
    {}

    span(span&& other) noexcept
            : fixed_begin{std::make_move_iterator(std::move(other.begin()))}
            , fixed_end{std::make_move_iterator(std::move(other.end()))}
            , fixed_size{std::move(other.size())}
    {}
    
    template <typename Container>
    span(Container&& other)
            : fixed_begin{ranges::begin(other)}
            , fixed_end{ranges::end(other)}
            , fixed_size{ranges::size(other)}
    {}

    span(const span&) = delete;
    auto operator=(const span&) = delete;
    auto operator=(span&&) noexcept = delete;

public cpp_operators:
    template <template <typename> typename Container>
    auto operator==(Container<T>&& other) const -> bool {return data() == other.data();}
    
    template <template <typename> typename Container>
    auto operator<=>(Container<T>&& other) const {return data() <=> other.data();}

public cpp_members:
    auto data() {return fixed_begin;}
    auto empty() {return fixed_size == 0;}
    auto size() {return fixed_size;}
    auto size_bytes() {return fixed_size * sizeof(element_type);}

    auto begin() {return fixed_begin;}
    auto rbegin() {return ranges::reverse_iterator<begin_iterator>{fixed_begin};}
    auto front() {return *fixed_begin;}

    auto end() {return fixed_end;}
    auto rend() {return ranges::reverse_iterator<end_iterator>{fixed_end};}
    auto back() {return *fixed_end;}

    auto first(size_type count) {return span{fixed_begin, count};}
    auto last(size_type count) {return span{ranges::prev(fixed_end, count), count};}
    auto subspan() {return span{fixed_begin, fixed_end};}
    auto subspan(size_type offset, size_type count) {return span{ranges::next(fixed_begin, offset), count};}

    [[deprecated("Use ..._span.at(...)")]]
    auto operator[](size_type index) -> element_type {return *ranges::next(fixed_begin, index);}
    auto at(size_type index) -> element_type {return *ranges::next(fixed_begin, index);}

private:
    const begin_iterator fixed_begin;
    const end_iterator fixed_end;
    const size_type fixed_size;
};

template <typename T, typename Iter>
using same_iterator_span = ext::span<T, Iter, Iter>;

template <typename T, size_t N>
using array_span = ext::same_iterator_span<T, typename ext::array<T, N>::const_iterator>;

template <typename K, typename V>
using map_span = ext::same_iterator_span<V, typename ext::map<K, V>::const_iterator>;

template <typename T>
using queue_span = ext::same_iterator_span<T, const typename ext::queue<T>::pointer>;

template <typename T>
using set_span = ext::same_iterator_span<T, typename ext::set<T>::const_iterator>;

template <typename T>
using stack_span = ext::same_iterator_span<T, const typename ext::stack<T>::pointer>;

template <typename T>
using vector_span = ext::same_iterator_span<T, typename ext::vector<T>::const_iterator>;

_EXT_END


#endif //SBROWSER2_SRC_EXT_SPAN_HPP
