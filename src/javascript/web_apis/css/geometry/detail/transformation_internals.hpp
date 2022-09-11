#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DETAIL_TRANSFORMATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DETAIL_TRANSFORMATION_INTERNALS_HPP

namespace css::geometry {class dom_point;}
namespace css::geometry {class dom_point_readonly;}
namespace css::geometry {class dom_matrix_readonly;}


namespace css::detail
{
    auto transform_point_with_matrix(
            geometry::dom_point_readonly* point,
            geometry::dom_matrix_readonly* matrix)
            -> geometry::dom_point;

    template <typename T, typename U>
    auto pre_multiply(T&& a, U&& b) -> T;

    template <typename T, typename U>
    auto post_multiply(T&& a, U&& b) -> U;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_GEOMETRY_DETAIL_TRANSFORMATION_INTERNALS_HPP
