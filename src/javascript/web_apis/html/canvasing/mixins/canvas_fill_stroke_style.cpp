#include "canvas_fill_stroke_style.hpp"

#include INCLUDE_INNER_TYPES(dom)

#include "dom/detail/exception_internals.hpp"
#include "html/canvasing/canvas_gradient.hpp"
#include "html/canvasing/canvas_pattern.hpp"
#include "html/detail/canvas_internals.hpp"

#include <QtGui/QLinearGradient>
#include <QtGui/QRadialGradient>
#include <QtGui/QConicalGradient>


auto html::canvasing::mixins::canvas_fill_stroke_style::create_linear_gradient(
        ext::number<double> x0,
        ext::number<double> x1,
        ext::number<double> y0,
        ext::number<double> y1)
        -> canvas_gradient
{
    auto gradient = canvas_gradient{};
    gradient.m_gradient = QLinearGradient{*x0, *y0, *x1, *y1};
    return gradient;
}


auto html::canvasing::mixins::canvas_fill_stroke_style::create_radial_gradient(
        ext::number<double> x0,
        ext::number<double> x1,
        ext::number<double> y0,
        ext::number<double> y1,
        ext::number<double> r0,
        ext::number<double> r1)
        -> canvas_gradient
{
    dom::detail::throw_v8_exception<INDEX_SIZE_ERR>(
            [r0, r1] {return r0 < 0 || r1 < 0;},
            "Radii must be >= 0");

    return_if (x0 == x1 && y0 == y1 && r0 == r1) canvas_gradient{};

    auto gradient = canvas_gradient{};
    gradient.m_gradient = QRadialGradient{*x0, *y0, *r0, *x1, *y1, *r1};
    return gradient;
}


auto html::canvasing::mixins::canvas_fill_stroke_style::create_conic_gradient(
        ext::number<double> start_angle,
        ext::number<double> x,
        ext::number<double> y)
        -> canvas_gradient
{
    auto gradient = canvas_gradient{};
    gradient.m_gradient = QConicalGradient{*x, *y, *start_angle};
    return gradient;
}


auto html::canvasing::mixins::canvas_fill_stroke_style::create_pattern(
        detail::canvas_image_source_t&& image,
        canvas_pattern_repeat_t repetition)
        -> canvas_pattern
{
    return_if (!detail::check_usability_of_image_argument(std::move(image))) canvas_pattern{};
    repetition = repetition == canvas_pattern_repeat_t::_ ? canvas_pattern_repeat_t::REPEAT : repetition;

    auto pattern = canvas_pattern{};
    pattern.m_image = std::move(image);
    pattern.m_repetition = repetition;
    pattern.m_origin_clean = ext::visit([](auto&& image_source) {return image_source.m_origin_clean;}, std::move(image));

    return pattern;
}
