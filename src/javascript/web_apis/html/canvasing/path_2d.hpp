#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_PATH_2D_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_PATH_2D_HPP


#include "mixins/canvas_path.hpp"
namespace html::canvasing {class path_2d;}

#include INCLUDE_INNER_TYPES(css/geometry)
#include <qpainterpath.h>


class html::canvasing::path_2d
        : public virtual dom_object
        , public mixins::canvas_path
{
public constructors:
    path_2d(const path_2d& path);
    path_2d(ext::string_view path = "");

public js_methods:
    auto add_path(path_2d* path, css::detail::dom_matrix2d_init_t&& transform = {});

private cpp_properties:
    QPainterPath m_path;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_PATH_2D_HPP
