#include "canvas_internals.hpp"

#include "html/canvasing/image_bitmap.hpp"
#include "html/canvasing/mixins/canvas_draw_path.hpp"
#include "html/canvasing/mixins/canvas_path_drawing_styles.hpp"

#include "webgl2/contexts/webgl_rendering_context.hpp"
#include "webgl2/contexts/webgl2_rendering_context.hpp"

#include <qcolor.h>
#include <qbrush.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpen.h>
#include <qpoint.h>


auto html::detail::fill_steps(
        canvasing::mixins::canvas_draw_path* context,
        canvasing::path_2d* path,
        detail::canvas_fill_rule_t fill_rule)
        -> void
{
    decltype(auto) fill_style = ext::variant_transform<detail::rendering_context_t, ext::string>(
            [](auto&& context) {return context->m_fill_style;});

    decltype(auto) bitmap = ext::variant_transform<detail::rendering_context_t, canvasing::image_bitmap*>(
            [](auto&& context) {return context->canvas()->m_image_bitmap;});

    auto painter = QPainter{&bitmap->m_bitmap_data};
    painter.setBrush(QBrush{fill_style.c_str()});
    painter.drawPolygon(path->m_path.toFillPolygon(), std::bit_cast<Qt::FillRule>(fill_rule));
}


auto html::detail::stroke_steps(
        canvasing::mixins::canvas_draw_path* context,
        canvasing::path_2d* path)
        -> void
{
    decltype(auto) stroke_style = ext::variant_transform<detail::rendering_context_t, ext::string>(
            [](auto&& context) {return context->m_stroke_style;});

    decltype(auto) bitmap = ext::variant_transform<detail::rendering_context_t, canvasing::image_bitmap*>(
            [](auto&& context) {return context->canvas()->m_image_bitmap;});

    auto traced_path = trace_path(ext::cross_cast<canvasing::mixins::canvas_path_drawing_styles*>(context), path);
    auto painter = QPainter{&bitmap->m_bitmap_data};
    painter.setPen(QPen{QColor{stroke_style.c_str()}});
    painter.setBrush(QBrush{Qt::GlobalColor::transparent});
    painter.drawPolygon(traced_path.m_path.toFillPolygon(), Qt::FillRule::WindingFill);
}


auto html::detail::clip_steps(
        canvasing::mixins::canvas_draw_path* context,
        canvasing::path_2d* path)
        -> void
{
    decltype(auto) bitmap = ext::variant_transform<detail::rendering_context_t, canvasing::image_bitmap*>(
            [](auto&& context) {return context->canvas()->m_image_bitmap;});

    auto painter = QPainter{&bitmap->m_bitmap_data};
    painter.setClipPath(path->m_path);
    painter.clipPath();
}


auto html::detail::is_point_in_path_steps(
        canvasing::mixins::canvas_draw_path* context,
        canvasing::path_2d* path,
        ext::number<double> x,
        ext::number<double> y,
        detail::canvas_fill_rule_t fill_rule)
        -> ext::boolean
{
    return_if (ext::is_inf_or_nan(x, y)) false;

    auto cloned_path = auto{*path};
    cloned_path.close_path();
    return cloned_path.m_path.contains(QPointF{*x, *y});
}


auto html::detail::is_point_in_stroke_steps(
        canvasing::mixins::canvas_draw_path* context,
        canvasing::path_2d* path,
        ext::number<double> x,
        ext::number<double> y)
        -> ext::boolean
{
    return_if (ext::is_inf_or_nan(x, y)) false;

    auto traced_path = trace_path(ext::cross_cast<canvasing::mixins::canvas_path_drawing_styles*>(context), path);
    return traced_path.m_path.contains(QPointF{*x, *y});
}
