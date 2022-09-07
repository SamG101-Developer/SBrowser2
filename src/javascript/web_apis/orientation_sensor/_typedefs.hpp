#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"
namespace css::geometry {class dom_matrix;}


namespace orientation_sensor::detail
{
    enum class orientation_sensor_local_coordinate_system_t {DEVICE, SCREEN};

    using rotation_matrix_type_t = ext::variant<ext::vector<float>, ext::vector<double>, css::geometry::dom_matrix*>;
    using orientation_sensor_options_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ORIENTATION_SENSOR__TYPEDEFS_HPP
