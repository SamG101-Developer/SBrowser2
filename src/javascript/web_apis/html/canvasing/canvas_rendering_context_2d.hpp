#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_RENDERING_CONTEXT_2D_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_RENDERING_CONTEXT_2D_HPP


#include "html/canvasing/mixins/canvas_state.hpp"
#include "html/canvasing/mixins/canvas_transform.hpp"
#include "html/canvasing/mixins/canvas_compositing.hpp"
#include "html/canvasing/mixins/canvas_image_smoothing.hpp"
#include "html/canvasing/mixins/canvas_fill_stroke_style.hpp"
#include "html/canvasing/mixins/canvas_shadow_styles.hpp"
#include "html/canvasing/mixins/canvas_filters.hpp"
#include "html/canvasing/mixins/canvas_rect.hpp"
#include "html/canvasing/mixins/canvas_draw_path.hpp"
#include "html/canvasing/mixins/canvas_user_interface.hpp"
#include "html/canvasing/mixins/canvas_text.hpp"
#include "html/canvasing/mixins/canvas_draw_image.hpp"
#include "html/canvasing/mixins/canvas_image_data.hpp"
#include "html/canvasing/mixins/canvas_path_drawing_styles.hpp"
#include "html/canvasing/mixins/canvas_text_drawing_styles.hpp"
#include "html/canvasing/mixins/canvas_path.hpp"
namespace html::canvasing {class canvas_rendering_context_2d;}

#include INCLUDE_INNER_TYPES(html)
namespace html::elements {class html_canvas_element;}
namespace html::canvasing {class canvas_rendering_context_2d_settings;}


class html::canvasing::canvas_rendering_context_2d
        : public virtual dom_object
        , public mixins::canvas_state
        , public mixins::canvas_transform
        , public mixins::canvas_compositing
        , public mixins::canvas_image_smoothing
        , public mixins::canvas_fill_stroke_style
        , public mixins::canvas_shadow_styles
        , public mixins::canvas_filters
        , public mixins::canvas_rect
        , public mixins::canvas_draw_path
        , public mixins::canvas_user_interface
        , public mixins::canvas_text
        , public mixins::canvas_draw_image
        , public mixins::canvas_image_data
        , public mixins::canvas_path_drawing_styles
        , public mixins::canvas_text_drawing_styles
        , public mixins::canvas_path
{
public constructors:
    DOM_CTORS(canvas_rendering_context_2d);
    canvas_rendering_context_2d() = default;

public js_methods:
    auto get_context_attributes() -> canvas_rendering_context_2d_settings;

private js_properties:
    ext::property<elements::html_canvas_element*> canvas;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    ext::boolean m_alpha;
    ext::boolean m_desynchronized;
    detail::predefined_color_space_t m_color_space;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_RENDERING_CONTEXT_2D_HPP
