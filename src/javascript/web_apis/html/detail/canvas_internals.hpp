#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_CANVAS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_CANVAS_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/optional.hpp"
#include "ext/string.hpp"

#include USE_INNER_TYPES(html)

namespace dom::nodes {class node;}
namespace html::canvasing {class image_bitmap;}
namespace html::canvasing {class image_bitmap_rendering_context;}
namespace html::canvasing {class image_data;}
namespace html::canvasing {class path_2d;}
namespace html::canvasing::mixins {class canvas_draw_path;}
namespace html::canvasing::mixins {class canvas_shadow_styles;}
namespace html::canvasing::mixins {class canvas_text_drawing_styles;}
namespace html::canvasing::mixins {class canvas_path_drawing_styles;}
namespace file_api {class file;}


namespace html::detail
{
    template <typename T>
    auto context_creation_algorithm(
            ext::map<ext::string, ext::any>&& options)
            -> T*;

    auto set_bitmap_dimensions(
            const ext::number<int>& width,
            const ext::number<int>& height)
            -> void;

    auto trace_path(
            canvasing::mixins::canvas_path_drawing_styles* context)
            -> canvasing::path_2d;

    auto resolve_font_style_source_object(
            canvasing::mixins::canvas_text_drawing_styles* context)
            -> dom::nodes::node*;

    auto text_preparation_algorithm(
            ext::string_view text,
            canvasing::mixins::canvas_text_drawing_styles* context,
            const ext::number<double>& max_width)
            -> void; // TODO : return type, also requires CSS

    auto ensure_there_is_subpath(
            const detail::path_t& path,
            ext::pair<ext::number<double>, ext::number<double>>&& coordinate)
            -> ext::boolean;

    auto check_usability_of_image_argument(
            canvas_image_source_t image)
            -> ext::boolean;

    auto image_not_origin_clean(
            canvas_image_source_t image)
            -> ext::boolean;

    auto point_in_path(
            canvasing::mixins::canvas_draw_path* context,
            canvasing::path_2d* path,
            const ext::number<double>& x,
            const ext::number<double>& y,
            canvas_fill_rule_t fill_rule)
            -> ext::boolean;

    auto point_in_stroke(
            canvasing::mixins::canvas_draw_path* context,
            canvasing::path_2d* path,
            const ext::number<double>& x,
            const ext::number<double>& y)
            -> ext::boolean;

    auto initialize_image_data(
            canvasing::image_data* data,
            const ext::number<int>& rows,
            const ext::number<int>& pixels_per_row,
            ext::vector_view<char> source = {},
            detail::predefined_color_space_t default_color_space = predefined_color_space_t::SRGB)
            -> void;

    auto draw_shadow(
            canvasing::canvas_rendering_context_2d* context)
            -> void;

    auto draw_shape(
            canvasing::canvas_rendering_context_2d* context)
            -> void;

    auto set_image_bitmap_rendering_contexts_output_bitmap(
            canvasing::image_bitmap_rendering_context* context,
            const detail::image_bitmap_t& bitmap)
            -> void;

    auto convert_color_value_from_non_premult_to_premult(
            detail::color_t& color)
            -> detail::color_t&;

    auto convert_color_value_from_premult_to_non_premult(
            detail::color_t& color)
            -> detail::color_t&;

    auto serialization_of_bitmap_as_file(
            ext::string_view type,
            ext::any&& options)
            -> ext::optional<file_api::file>;
}


struct html::detail::image_bitmap_t
{
    ext::boolean origin_clean_flag = true;
};


struct html::detail::drawing_state_t
{
    canvasing::image_bitmap* bitmap;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_CANVAS_INTERNALS_HPP
