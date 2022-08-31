#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_GRADIENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_GRADIENT_HPP

#include "dom_object.hpp"
namespace html::canvasing {class canvas_gradient;}


class html::canvasing::canvas_gradient
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(canvas_gradient);
    canvas_gradient() = default;

public js_methods:
    auto add_color_stop(ext::number<double>&& offset, ext::string&& color);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_GRADIENT_HPP
