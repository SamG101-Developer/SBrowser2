module;
#include "ext/macros.hpp"


module apis.indexed_db.detail;

import apis.infra.detail;

import ext.core;
import ext.js;


auto indexed_db::detail::compare_two_keys(const ext::any& a, const ext::any& b) -> ext::number<int>
{
    if (a.type() != b.type())
    {
        // return_if(ext::type_is_any_specialization_of<T, ext::vector>) 1;
        // return_if(ext::type_is_any_specialization_of<U, ext::vector>) -1;
        return_if(a.type() == typeid(ext::u8string)) 1;
        return_if(b.type() == typeid(ext::u8string)) -1;
        return_if(a.type() == typeid(ext::string)) 1;
        return_if(b.type() == typeid(ext::string)) -1;
        return_if(a.type() == typeid(ext::date)) 1;
        return -1;
    }

    if (a.type() == typeid(ext::date) || a.type() == typeid(ext::number))
        return ext::three_way_compare(a, b);

    if (a.type() == typeid(ext::string))
        return ext::three_way_compare(a, b, infra::detail::code_unit_less_than);

    if (a.type() == typeid(ext::u8string))
        return ext::three_way_compare(a, b, infra::detail::byte_less_than);

    //if (ext::type_is_any_specialization_of<T, ext::vector>)
    //{
    //    auto length = ext::min(a.size(), b.size());
    //    auto comparisons = ranges::views::zip(a, b)
    //            | ranges::views::transform([](auto&& pair) {return compare_two_keys(pair.first, pair.second);})
    //            | ranges::views::remove(0);
    //
    //    return comparisons.empty() ? ext::three_way_compare(a.size(), b.size()) : comparisons.front();
    //}
}
