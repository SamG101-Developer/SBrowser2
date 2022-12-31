module;
#include "ext/macros.hpp"
#include <libgamepad.hpp>


export module apis.gamepad.gamepad:p;
import apis.dom_object;

IMPORT_ALL_TYPES(gamepad);
IMPORT_ALL_TYPES(hr_time);


DEFINE_PRIVATE_CLASS(gamepad, gamepad)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(gamepad);

public:
    auto select_unused_gamepad_index() const -> detail::gamepad_mapping_type_t;
    auto contains_gamepad_user_gesture() const -> ext::boolean;

public:
    ext::boolean connected = false;
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
    std::shared_ptr<::gamepad::device> platform_gamepad; // TODO : namespace conflict
};
