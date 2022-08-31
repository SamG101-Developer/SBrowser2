#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_SHADOW_STYLES_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_SHADOW_STYLES_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_shadow_styles;}


class html::canvasing::mixins::canvas_shadow_styles
        : public virtual dom_object
{
public js_properties:
    ext::property<ext::number<double>> shadow_offset_x;
    ext::property<ext::number<double>> shadow_offset_y;
    ext::property<ext::number<double>> shadow_blur;
    ext::property<ext::string> shadow_color;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_SHADOW_STYLES_HPP
