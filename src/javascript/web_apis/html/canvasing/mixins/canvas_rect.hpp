#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_RECT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_RECT_HPP



namespace html::canvasing::mixins {class canvas_rect;}


class html::canvasing::mixins::canvas_rect
        : public virtual dom_object
{
public js_methods:
    auto clear_rect (ext::number<double> x, ext::number<double> y, ext::number<double> w, ext::number<double> h) -> void;
    auto fill_rect  (ext::number<double> x, ext::number<double> y, ext::number<double> w, ext::number<double> h) -> void;
    auto stroke_rect(ext::number<double> x, ext::number<double> y, ext::number<double> w, ext::number<double> h) -> void;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_RECT_HPP
