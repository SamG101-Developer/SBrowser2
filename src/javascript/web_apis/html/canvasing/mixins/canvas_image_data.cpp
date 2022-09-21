#include "canvas_image_data.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(html)

#include "dom/detail/exception_internals.hpp"

#include "html/canvasing/canvas_rendering_context_2d.hpp"
#include "html/canvasing/image_bitmap.hpp"
#include "html/canvasing/image_data.hpp"
#include "html/detail/canvas_internals.hpp"
#include "html/elements/html_canvas_element.hpp"

#include <range/v3/action/transform.hpp>
#include <range/v3/view/transform.hpp>


auto html::canvasing::mixins::canvas_image_data::create_image_data(
        ext::number<long> sw,
        ext::number<long> sh,
        detail::image_data_settings_t&& settings)
        -> image_data
{
    dom::detail::throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [sw, sh] {return sw == 0 || sh == 0;},
            "'sw', 'sh' cannot be 0");

    auto color_space = ext::visit(
            [this]<typename T>(T*) {return dynamic_cast<T*>(this)->m_scolor_space;},
            detail::rendering_context_t{});

    auto new_image_data = image_data{ext::abs(sw), ext::abs(sh), std::move(settings)};
    new_image_data.color_space = color_space;
    new_image_data.m_canvas_pixel_array_buffer |= ranges::actions::transform([] {return detail::color_t{.r=0, .g=0, .b=0, .a=0};});
    return new_image_data;
}


auto html::canvasing::mixins::canvas_image_data::create_image_data(
        html::canvasing::image_data* data)
        -> image_data
{
    auto new_image_data = auto{*data};
    new_image_data.m_canvas_pixel_array_buffer |= ranges::actions::transform([] {return detail::color_t{.r=0, .g=0, .b=0, .a=0};});
    return new_image_data;
}


auto html::canvasing::mixins::canvas_image_data::get_image_data(
        ext::number<long> sx,
        ext::number<long> sy,
        ext::number<long> sw,
        ext::number<long> sh,
        detail::image_data_settings_t&& settings)
        -> image_data
{
    auto base = dynamic_cast<canvas_rendering_context_2d*>(this);

    dom::detail::throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [sw, sh] {return sw == 0 || sh == 0;},
            "'sw', 'sh' cannot be 0");

    dom::detail::throw_v8_exception_formatted<SECURITY_ERR>(
            [origin_clean = base->m_origin_clean] {return !origin_clean;},
            "Origin must be clean");

    auto current_image_data = image_data{};
    detail::initialize_image_data(current_image_data, sw, sh, std::move(settings), {}, base->m_color_space);

    current_image_data.m_canvas_pixel_array_buffer = base->canvas()->m_bitmap.get()->m_bitmap_data.copy(*sx, *sy, *sw, *sh).toImage().constBits()
            | ranges::views::transform([](auto&& data));
}
