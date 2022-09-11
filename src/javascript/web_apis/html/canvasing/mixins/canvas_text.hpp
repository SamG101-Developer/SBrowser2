#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_TEXT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_TEXT_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_text;}

namespace html::canvasing {class text_metrics;}


class html::canvasing::mixins::canvas_text
        : public virtual dom_object
{
public js_methods:
    auto fill_text  (ext::string&& text, ext::number<double> x, ext::number<double> y, ext::number<double> max_width = 0);
    auto stroke_text(ext::string&& text, ext::number<double> x, ext::number<double> y, ext::number<double> max_width = 0);
    auto measure_text(ext::string_view text) -> text_metrics;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_TEXT_HPP
