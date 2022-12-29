#include "canvas_draw_path.hpp"

#include "html/detail/canvas_internals.hpp"


auto html::canvasing::mixins::canvas_draw_path::begin_path() -> void
{m_current_default_path.reset();}


auto html::canvasing::mixins::canvas_draw_path::fill(detail::canvas_fill_rule_t fill_rule) -> void
{detail::fill_steps(this, m_current_default_path.get(), fill_rule);}


auto html::canvasing::mixins::canvas_draw_path::fill(html::canvasing::path_2d* path, detail::canvas_fill_rule_t fill_rule) -> void
{detail::fill_steps(this, path, fill_rule);}


auto html::canvasing::mixins::canvas_draw_path::stroke() -> void
{detail::stroke_steps(this, m_current_default_path.get());}


auto html::canvasing::mixins::canvas_draw_path::stroke(html::canvasing::path_2d* path) -> void
{detail::stroke_steps(this, path);}


auto html::canvasing::mixins::canvas_draw_path::clip(detail::canvas_fill_rule_t fill_rule) -> void
{detail::clip_steps(this, m_current_default_path.get());}


auto html::canvasing::mixins::canvas_draw_path::clip(html::canvasing::path_2d* path, detail::canvas_fill_rule_t fill_rule) -> void
{detail::clip_steps(this, path);}


auto html::canvasing::mixins::canvas_draw_path::is_point_in_path(ext::number<double> x, ext::number<double> y, detail::canvas_fill_rule_t fill_rule) -> ext::boolean
{return detail::is_point_in_path_steps(this, m_current_default_path.get(), x, y, fill_rule);}


auto html::canvasing::mixins::canvas_draw_path::is_point_in_path(html::canvasing::path_2d* path, ext::number<double> x, ext::number<double> y, detail::canvas_fill_rule_t fill_rule) -> ext::boolean
{return detail::is_point_in_path_steps(this, path, x, y, fill_rule);}


auto html::canvasing::mixins::canvas_draw_path::is_point_in_stroke(ext::number<double> x, ext::number<double> y) -> ext::boolean
{return detail::is_point_in_stroke_steps(this, m_current_default_path.get(), x, y);}


auto html::canvasing::mixins::canvas_draw_path::is_point_in_stroke(html::canvasing::path_2d* path, ext::number<double> x, ext::number<double> y) -> ext::boolean
{return detail::is_point_in_stroke_steps(this, path, x, y);}
