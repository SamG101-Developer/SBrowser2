#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_GRADIENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_GRADIENT_HPP


namespace html::canvasing {class canvas_gradient;}


#include <QtGui/QLinearGradient>
#include <QtGui/QRadialGradient>
#include <QtGui/QConicalGradient>


class html::canvasing::canvas_gradient
        : public virtual dom_object
{
public constructors:
    canvas_gradient();
    ~canvas_gradient() override;

public js_methods:
    auto add_color_stop(ext::number<double> offset, ext::string&& color);

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    ext::variant<QLinearGradient, QRadialGradient, QConicalGradient> m_gradient;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_GRADIENT_HPP
