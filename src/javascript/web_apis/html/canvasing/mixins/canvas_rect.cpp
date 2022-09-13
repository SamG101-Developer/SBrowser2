#include "canvas_rect.hpp"

#include "ext/variant.hpp"
#include "html/detail/canvas_internals.hpp"

#include USE_INNER_TYPES(html)

#include "html/canvasing/canvas_rendering_context_2d.hpp"
#include "html/canvasing/image_bitmap.hpp"
#include "html/canvasing/image_bitmap_rendering_context.hpp"
#include "html/canvasing/path_2d.hpp"
#include "html/canvasing/mixins/canvas_path_drawing_styles.hpp"
#include "html/elements/html_canvas_element.hpp"

#include "webgl2/contexts/webgl_rendering_context.hpp"
#include "webgl2/contexts/webgl2_rendering_context.hpp"

#include <qbrush.h>
#include <qpainter.h>


auto html::canvasing::mixins::canvas_rect::clear_rect(
        ext::number<double> x,
        ext::number<double> y,
        ext::number<double> w,
        ext::number<double> h)
        -> void
{
    decltype(auto) bitmap = ext::visit(
            [this]<typename T>(T* context) {return dynamic_cast<T*>(this)->canvas()->m_bitmap.get();},
            detail::rendering_context_t{});

    auto painter = QPainter{&bitmap->m_bitmap_data};
    painter.eraseRect(*x, *y, *w, *h);
    painter.end();
}


auto html::canvasing::mixins::canvas_rect::fill_rect(
        ext::number<double> x,
        ext::number<double> y,
        ext::number<double> w,
        ext::number<double> h)
        -> void
{
    decltype(auto) fill_style = ext::visit(
            [this]<typename T>(T*) {return dynamic_cast<T*>(this)->m_fill_style;},
            detail::rendering_context_t{});

    decltype(auto) bitmap = ext::visit(
            [this]<typename T>(T*) {return dynamic_cast<T*>(this)->canvas()->m_bitmap.get();},
            detail::rendering_context_t{});


    auto painter = QPainter{&bitmap->m_bitmap_data};
    painter.fillRect(*x, *y, *w, *h, QBrush{QColor{fill_style.c_str()}});
    painter.end();
}


auto html::canvasing::mixins::canvas_rect::stroke_rect(
        ext::number<double> x,
        ext::number<double> y,
        ext::number<double> w,
        ext::number<double> h)
        -> void
{
    decltype(auto) stroke_style = ext::visit(
            [this]<typename T>(T*) {return dynamic_cast<T*>(this)->m_stroke_style;},
            detail::rendering_context_t{});

    decltype(auto) bitmap = ext::visit(
            [this]<typename T>(T* context) {return dynamic_cast<T*>(this)->canvas()->m_image_bitmap;},
            detail::rendering_context_t{});


    auto painter = QPainter{&bitmap->m_bitmap_data};
    auto path = detail::trace_path(ext::cross_cast<html::canvasing::mixins::canvas_path_drawing_styles*>(this));
    painter.strokePath(path.m_path, stroke_style);
    painter.end();
}
