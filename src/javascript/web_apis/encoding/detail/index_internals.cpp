#include "index_internals.hpp"

#include "ext/filesystem.ixx"
#include "ext/functional.ixx"
#include "ext/pair.ixx"
#include "ext/ranges.hpp"


template <typename T>
auto encoding::detail::index_gb18030_ranges_code_point(typename T::iterator& pointer) -> typename T::value_type
{
    return_if (*pointer > 39419 && *pointer < 189000 || *pointer > 1237575) 0;
    return_if (*pointer == 7475) T(0xE7C7);

    auto parsed = ext::filesystem::fs::open("ranges/gb18030.csv").readFile() | ranges::views::parse_csv();
    auto offset = ranges::back(parsed
            | ranges::views::transform(ext::get_pair_key)
            | ranges::views::filter(BIND_FRONT(ext::cmp::le, *pointer)));
    auto code_point_offset = parsed.at(offset);

    return T::value_type(code_point_offset + pointer - offset);
}


template <typename T>
auto index_gb1030_ranges_pointer(typename T::value_type code_point) -> ext::string::iterator&
{
    return_if (code_point == T::value_type(0xE7C7));
    // TODO
}
