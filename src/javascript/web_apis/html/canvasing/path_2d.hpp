#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_PATH_2D_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_PATH_2D_HPP

#include "dom_object.hpp"
#include "mixins/canvas_path.hpp"
namespace html::canvasing {class path_2d;}


class html::canvasing::path_2d
        : public virtual dom_object
        , public mixins::canvas_path
{
public constructors:
    DOM_CTORS(path_2d);

    template <type_is<path_2d*, ext::string> T>
    path_2d(T&& path = nullptr);

public js_methods:
    auto add_path(path_2d* path, css::detail::dom_matrix_2d_init&& transform = {});
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_PATH_2D_HPP
