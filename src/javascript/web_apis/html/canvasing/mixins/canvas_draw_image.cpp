#include "canvas_draw_image.hpp"

#include INCLUDE_INNER_TYPES(html)

#include "html/detail/canvas_internals.hpp"
#include "html/canvasing/canvas_rendering_context_2d.hpp"
#include "html/canvasing/image_bitmap.hpp"
#include "html/canvasing/offscreen_canvas.hpp"
#include "html/elements/html_canvas_element.hpp"
#include "html/elements/html_image_element.hpp"
#include "html/elements/html_video_element.hpp"

#include "webgl2/contexts/webgl_rendering_context.hpp"
#include "webgl2/contexts/webgl2_rendering_context.hpp"

#include <qimage.h>
#include <qpainter.h>


auto html::canvasing::mixins::canvas_draw_image::draw_image(
        detail::canvas_image_source_t image,
        ext::number<double> dx,
        ext::number<double> dy)
        -> void
{
    draw_image(image, dx, dy, 0, 0);
}


auto html::canvasing::mixins::canvas_draw_image::draw_image(
        detail::canvas_image_source_t image,
        ext::number<double> dx,
        ext::number<double> dy,
        ext::number<double> dw,
        ext::number<double> dh)
        -> void
{
    auto sw = ext::visit([](auto&& true_image) -> ext::number<ulong> {return true_image->width ();}, std::move(image));
    auto sh = ext::visit([](auto&& true_image) -> ext::number<ulong> {return true_image->height();}, std::move(image));
    draw_image(0, 0, sw, sh, dx, dy, dw, dh);
}


auto html::canvasing::mixins::canvas_draw_image::draw_image(
        detail::canvas_image_source_t image,
        ext::number<double> sx,
        ext::number<double> sy,
        ext::number<double> sw,
        ext::number<double> sh,
        ext::number<double> dx,
        ext::number<double> dy,
        ext::number<double> dw,
        ext::number<double> dh)
        -> void
{
    return_if (ext::is_inf_or_nan(dx, dy));
    return_if (!detail::check_usability_of_image_argument(image));
    return_if (sw == 0 || sh == 0);

    decltype(auto) bitmap = ext::visit(
            [this]<typename T>(T*) {return dynamic_cast<T*>(this)->canvas()->m_bitmap.get();},
            detail::rendering_context_t{});

    auto painter = QPainter{&bitmap->m_bitmap_data};
    painter.drawImage(dx, dy, QImage::fromData("TODO: from 'image'", dw * dh), sx, sy, sw, sh);
    painter.end(); // TODO : image-smoothing

    if (!ext::visit([](auto&& true_image) {return true_image->m_origin_clean;}, std::move(image)))
        ext::visit([this]<typename T>(T* context) {dynamic_cast<T*>(this)->m_origin_clean = false;}, detail::rendering_context_t{});
}
