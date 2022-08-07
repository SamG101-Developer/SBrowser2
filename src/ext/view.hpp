#ifndef SBROWSER2_SRC_EXT_VIEW_HPP
#define SBROWSER2_SRC_EXT_VIEW_HPP

#include "ext/concepts.hpp"
#include <iterator>
#include <span>


_EXT_BEGIN

template <iterator_like _Tx>
class view
{
public aliases:
    using iterator = _Tx;
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
    view(iterator* begin, iterator* end)
            : _Begin{begin}
            , _End{end}
            , _Size{std::distance(begin, end)}
    {}

    view(iterator* begin, size_type size)
            : _Begin{begin}
            , _End{std::next(begin, size)}
            , _Size{size}
    {}

    view(view&& other) noexcept
            : _Begin(std::move(other.begin()))
            , _End(std::move(other.end()))
            , _Size(std::move(other.size()))
    {}

    view(const view&) = delete;
    auto operator=(const view&) = delete;
    auto operator=(view&&) noexcept = delete;

public cpp_methods:
    auto data() -> iterator {return _Begin;}
    auto empty() -> bool {return _Size == 0;}
    auto size() -> size_type {return _Size;}

    auto begin() -> iterator {return _Begin;}
    auto rbegin() -> reverse_iterator {return std::reverse_iterator{_Begin};}
    auto front() -> element_type {return *_Begin;}

    auto end() -> iterator {return _End;}
    auto rend() -> reverse_iterator {return reverse_iterator{_End};}
    auto back() -> element_type {return *_End;}

    auto first(size_type count) -> view<iterator> {return view{_Begin, count};}
    auto last(size_type count) -> view<iterator> {return view{std::prev(_End, count), count};}
    auto subspan() -> view<iterator> {return view{_Begin, _End};}
    auto subspan(size_type offset, size_type count) {return view{std::next(_Begin, offset), count};}

private cpp_properties:
    iterator _Begin;
    iterator _End;
    size_type _Size;
};

_EXT_END

#endif //SBROWSER2_SRC_EXT_VIEW_HPP
