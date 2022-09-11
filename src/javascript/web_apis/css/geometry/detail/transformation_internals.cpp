#include "transformation_internals.hpp"

#include "css/geometry/dom_point.hpp"
#include "css/geometry/dom_matrix.hpp"

#include <QtGui/QVector4D>
#include <QtGui/QMatrix4x4>


auto css::detail::transform_point_with_matrix(
        geometry::dom_point_readonly* point,
        geometry::dom_matrix_readonly* matrix)
        -> geometry::dom_point
{
    auto p = pre_multiply(point.m_point, matrix.m_matrix);
    return geometry::dom_point::from_point({{"x", p.x()}, {"y", p.y()}, {"z", p.z()}, {"w", p.w()}});
}
