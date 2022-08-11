#ifndef SBROWSER2_SRC_EXT_VIEW_HPP
#define SBROWSER2_SRC_EXT_VIEW_HPP

#include "ext/concepts.hpp"
#include "ext/keywords.hpp"
#include <iterator>
#include <span>


_EXT_BEGIN

template <typename T>
class view
{
public aliases:
    using iterator = T;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using pointer = std::remove_pointer_t<iterator>;
    using reference = std::remove_pointer_t<pointer>&;
    using element_type = std::remove_pointer_t<pointer>;
    using value_type = std::remove_cv_t<element_type>;
    using const_pointer = const pointer;
    using const_reference = const reference;
    using difference_type = ptrdiff_t;
    using size_type = size_t;

public constructors:
    view()
            : fixed_begin(nullptr)
            , fixed_end(nullptr)
            , fixed_size(0)
    {};

    view(const iterator begin, const iterator end)
            : fixed_begin{begin}
            , fixed_end{end}
            , fixed_size{std::distance(begin, end)}
    {}

    view(const iterator begin, size_type size)
            : fixed_begin{begin}
            , fixed_end{std::next(begin, size)}
            , fixed_size{size}
    {}

    view(view&& other) noexcept
            : fixed_begin(std::move(other.begin()))
            , fixed_end(std::move(other.end()))
            , fixed_size(std::move(other.size()))
    {}

    view(const view&) = delete;
    auto operator=(const view&) = delete;
    auto operator=(view&&) noexcept = delete;

public cpp_methods:
    auto data() -> iterator {return fixed_begin;}
    auto empty() -> bool {return fixed_size == 0;}
    auto size() -> size_type {return fixed_size;}

    auto begin() -> iterator {return fixed_begin;}
    auto rbegin() -> reverse_iterator {return std::reverse_iterator{fixed_begin};}
    auto front() -> element_type {return *fixed_begin;}

    auto end() -> iterator {return fixed_end;}
    auto rend() -> reverse_iterator {return reverse_iterator{fixed_end};}
    auto back() -> element_type {return *fixed_end;}

    auto first(size_type count) -> view<iterator> {return view{fixed_begin, count};}
    auto last(size_type count) -> view<iterator> {return view{std::prev(fixed_end, count), count};}
    auto subspan() -> view<iterator> {return view{fixed_begin, fixed_end};}
    auto subspan(size_type offset, size_type count) {return view{std::next(fixed_begin, offset), count};}

    auto at(size_type where) -> element_type {return *std::next(fixed_begin, where);}

private cpp_properties:
    const iterator fixed_begin;
    const iterator fixed_end;
    const size_type fixed_size;
};

_EXT_END

#endif //SBROWSER2_SRC_EXT_VIEW_HPP
