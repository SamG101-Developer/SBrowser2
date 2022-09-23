#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_TEXT_DRAWING_STYLES_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_TEXT_DRAWING_STYLES_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_text_drawing_styles;}

#include INCLUDE_INNER_TYPES(html)


class html::canvasing::mixins::canvas_text_drawing_styles
        : public virtual dom_object
{
private js_properties:
    ext::property<ext::string> font;
    ext::property<detail::canvas_text_align_t> text_align;
    ext::property<detail::canvas_text_baseline_t> text_baseline;
    ext::property<detail::canvas_direction_t> text_direction;
    ext::property<detail::canvas_text_rendering_t> text_rendering;

    ext::property<detail::canvas_font_kerning_t> font_kerning;
    ext::property<detail::canvas_font_stretch_t> font_stretch;
    ext::property<detail::canvas_font_variant_caps_t> font_variant_caps;

    ext::property<ext::string> letter_spacing;
    ext::property<detail::canvas_text_align_t> word_spacing;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_TEXT_DRAWING_STYLES_HPP
