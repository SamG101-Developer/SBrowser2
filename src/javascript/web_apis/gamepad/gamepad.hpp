#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_HPP

#include "dom_object.hpp"
namespace gamepad {class gamepad;}
namespace gamepad {class gamepad_private;}

#include INCLUDE_INNER_TYPES(gamepad)
#include INCLUDE_INNER_TYPES(hr_time)
#include "ext/span.hpp"
namespace gamepad {class gamepad_button;}


class gamepad::gamepad
        : public virtual dom_object
{
public constructors:
    gamepad();
    MAKE_PIMPL(gamepad);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(id, ext::string_view);
    DEFINE_GETTER(index, ext::number<long>);
    DEFINE_GETTER(connected, ext::boolean);

    DEFINE_GETTER(timestamp, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(mapping, detail::gamepad_mapping_type_t);
    DEFINE_GETTER(axes, ext::vector_span<ext::number<double>>);
    DEFINE_GETTER(buttons, ext::vector_span<gamepad_button*>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_HPP
