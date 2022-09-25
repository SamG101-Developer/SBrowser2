#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_HPP

#include "dom_object.hpp"
namespace gamepad {class gamepad;}

#include INCLUDE_INNER_TYPES(gamepad)
#include INCLUDE_INNER_TYPES(hr_time)
namespace gamepad {class gamepad_button;}

#include "gamepad_private.hpp"


class gamepad::gamepad
        : public virtual dom_object
{
public constructors:
    gamepad();
    MAKE_PIMPL(gamepad);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(id, ext::string);
    DEFINE_GETTER(index, ext::number<long>);
    DEFINE_GETTER(connected, ext::boolean);

    DEFINE_GETTER(timestamp, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(mapping, detail::gamepad_mapping_type_t);
    DEFINE_GETTER(axes, ext::vector_view<ext::number<double>>);
    DEFINE_GETTER(buttons, ext::vector_view<gamepad_button*>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_HPP
