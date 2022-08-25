#include "encoding_internals.hpp"

#include "infra/detail/code_points_internals.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/iota.hpp>


auto url::detail::is_c0_control_percent_encodable(
        wchar_t code_point)
        -> ext::boolean
{
    return infra::detail::code_points_internals::is_c0_control(code_point) || code_point > 0x007e;
}


auto url::detail::is_fragment_percent_encodable(
        wchar_t code_point)
        -> ext::boolean
{
    auto fragment_code_point_set = {0x0020, 0x0022, 0x003c, 0x003e, 0x0060};
    return is_c0_control_percent_encodable(code_point) || ranges::contains(fragment_code_point_set, code_point);
}


auto url::detail::is_query_percent_encodable(
        wchar_t code_point)
        -> ext::boolean
{
    auto query_code_point_set = {0x0020, 0x0022, 0x002c, 0x003c, 0x003e};
    return is_c0_control_percent_encodable(code_point) || ranges::contains(query_code_point_set, code_point);
}


auto url::detail::is_special_percent_encodable(
        wchar_t code_point)
        -> ext::boolean
{
    auto special_code_point_set = {0x0027};
    return is_query_percent_encodable(code_point) || ranges::contains(special_code_point_set, code_point);
}


auto url::detail::is_path_percent_encodable(
        wchar_t code_point)
        -> ext::boolean
{
    auto path_code_point_set = {0x003f, 0x0060, 0x007b, 0x007d};
    return is_query_percent_encodable(code_point) || ranges::contains(path_code_point_set, code_point);
}


auto url::detail::is_userinfo_percent_encodable(
        wchar_t code_point)
        -> ext::boolean
{
    auto userinfo_code_point_set1 = {0x002f, 0x003a, 0x003b, 0x003d, 0x0040, 0x007c};
    auto userinfo_code_point_set2 = ranges::views::closed_iota(0x005b, 0x005e);
    auto userinfo_code_point_set = ranges::views::concat(userinfo_code_point_set1, userinfo_code_point_set2);
    return is_path_percent_encodable(code_point) || ranges::contains(userinfo_code_point_set, code_point);
}
