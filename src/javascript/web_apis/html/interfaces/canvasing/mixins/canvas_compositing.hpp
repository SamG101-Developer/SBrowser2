#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_COMPOSITING_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_COMPOSITING_HPP


namespace html::canvasing::mixins {class canvas_compositing;}


class html::canvasing::mixins::canvas_compositing
        : public virtual dom_object
{
private js_properties:
    ext::property<ext::number<double>> global_alpha;
    ext::property<ext::string> global_composite_operation;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_COMPOSITING_HPP
