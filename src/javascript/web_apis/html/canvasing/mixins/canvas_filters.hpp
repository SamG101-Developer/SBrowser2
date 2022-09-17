#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_FILTERS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_FILTERS_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_filters;}


class html::canvasing::mixins::canvas_filters
        : public virtual dom_object
{
public js_properties:
    ext::property<ext::string> filter;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

public cpp_properties:
    DEFINE_CUSTOM_SETTER(filter);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_FILTERS_HPP
