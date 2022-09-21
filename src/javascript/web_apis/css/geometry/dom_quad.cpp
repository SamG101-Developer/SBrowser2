#include "dom_quad.hpp"

#include "css/geometry/dom_point.hpp"


css::geometry::dom_quad::dom_quad(
        detail::dom_point_init_t&& p1,
        detail::dom_point_init_t&& p2,
        detail::dom_point_init_t&& p3,
        detail::dom_point_init_t&& p4)
{
    d_ptr->emplace_back(*p1.try_emplace("x", 0.0).first->second.to<ext::number<double>>(), *p1.try_emplace("y", 0.0).first->second.to<ext::number<double>>());
    d_ptr->emplace_back(*p2.try_emplace("x", 0.0).first->second.to<ext::number<double>>(), *p2.try_emplace("y", 0.0).first->second.to<ext::number<double>>());
    d_ptr->emplace_back(*p3.try_emplace("x", 0.0).first->second.to<ext::number<double>>(), *p3.try_emplace("y", 0.0).first->second.to<ext::number<double>>());
    d_ptr->emplace_back(*p4.try_emplace("x", 0.0).first->second.to<ext::number<double>>(), *p4.try_emplace("y", 0.0).first->second.to<ext::number<double>>());
}


auto css::geometry::dom_quad::from_rect(
        detail::dom_rect_init_t&& other)
        -> dom_quad
{
    auto x = other.try_emplace("x", 0.0).first->second.to<ext::number<double>>();
    auto y = other.try_emplace("y", 0.0).first->second.to<ext::number<double>>();
    auto w = other.try_emplace("w", 0.0).first->second.to<ext::number<double>>();
    auto h = other.try_emplace("h", 0.0).first->second.to<ext::number<double>>();

    return dom_quad
    {
            {{"x", x}, {"y", y}, {"z", 0}, {"w", 1}},
            {{"x", x + w}, {"y", y}, {"z", 0}, {"w", 1}},
            {{"x", x + w}, {"y", y + h}, {"z", 0}, {"w", 1}},
            {{"x", x}, {"y", y + h}, {"z", 0}, {"w", 1}}
    };
}


auto css::geometry::dom_quad::from_quad(
        detail::dom_quad_init_t&& other)
        -> dom_quad
{
    return dom_quad
    {
        other.try_emplace("p1").first->second.to<detail::dom_point_init_t&&>(),
        other.try_emplace("p2").first->second.to<detail::dom_point_init_t&&>(),
        other.try_emplace("p3").first->second.to<detail::dom_point_init_t&&>(),
        other.try_emplace("p4").first->second.to<detail::dom_point_init_t&&>()
    };
}
