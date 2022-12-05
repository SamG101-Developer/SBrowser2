#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_USER_INTERFACE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_USER_INTERFACE_HPP


namespace html::canvasing::mixins {class canvas_user_interface;}

namespace dom::nodes {class element;}
namespace html::canvasing {class path_2d;}


class html::canvasing::mixins::canvas_user_interface
        : public virtual dom_object
{
public js_methods:
    auto draw_if_focus_needed(dom::nodes::element* element) -> void;
    auto draw_if_focus_needed(path_2d* path, dom::nodes::element* element) -> void;
    auto scroll_path_into_view() -> void;
    auto scroll_path_into_view(path_2d* path) -> void;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};



#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_USER_INTERFACE_HPP
