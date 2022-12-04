#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"



#include "ext/vector.hpp"

#include INCLUDE_INNER_TYPES(gamepad)
#include INCLUDE_INNER_TYPES(hr_time)

namespace gamepad {class gamepad_button;}


DEFINE_PRIVATE_CLASS(gamepad, gamepad) : virtual dom_object_private
{
    ext::boolean connected;
    hr_time::dom_high_res_time_stamp timestamp;
    ext::vector<ext::number<double>> axes;
    ext::vector<gamepad_button*> buttons;
    ext::boolean exposed;

    ext::map<ext::number<int>, ext::number<int>> axis_mapping;
    ext::vector<ext::number<int>> axis_minimums;
    ext::vector<ext::number<int>> axis_maximums;

    ext::map<ext::number<int>, gamepad_button*> button_mapping;
    ext::vector<ext::number<int>> button_minimums;
    ext::vector<ext::number<int>> button_maximums;

    ext::string id;
    detail::gamepad_mapping_type_t mapping;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_PRIVATE_HPP
