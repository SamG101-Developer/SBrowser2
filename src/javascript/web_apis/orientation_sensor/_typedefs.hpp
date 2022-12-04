#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR__TYPEDEFS_HPP





#include "ext/vector.hpp"

#include INCLUDE_INNER_TYPES(javascript)

namespace css::geometry {class dom_matrix;}


namespace orientation_sensor::detail
{
    enum class orientation_sensor_local_coordinate_system_t {DEVICE, SCREEN};

    using rotation_matrix_type_t = ext::variant<
            ext::vector<ext::number<double>>,
            css::geometry::dom_matrix*>;
    using orientation_sensor_options_t = ext::map<ext::string, ext::any>;
    using absolute_orientation_sensor_options_t = ext::map<ext::string, ext::any>;
    using relative_orientation_sensor_options_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR__TYPEDEFS_HPP
