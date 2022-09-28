#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_READONLY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_READONLY_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include <qmatrix4x4.h>


DEFINE_PRIVATE_CLASS(css::geometry, dom_matrix_readonly) : dom_object_private
{
    QMatrix4x4 matrix;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DOM_MATRIX_READONLY_PRIVATE_HPP
