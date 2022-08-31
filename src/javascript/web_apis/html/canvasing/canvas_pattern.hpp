#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_PATTERN_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_PATTERN_HPP

#include "dom_object.hpp"
namespace html::canvasing {class canvas_pattern;}

#include USE_INNER_TYPES(css/geometry)


class html::canvasing::canvas_pattern
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(canvas_pattern);
    canvas_pattern() = default;

public js_methods:
    auto set_transform(css::detail::dom_matrix2d_init&& transform = {});
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_CANVAS_PATTERN_HPP
