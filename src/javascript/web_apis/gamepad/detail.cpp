module;
#include "ext/macros/language_shorthand.hpp"
#include <chrono>
#include <libgamepad.hpp>
#include <range/v3/view/filter.hpp>


module apis.gamepad.detail;
import apis.gamepad.gamepad;
import apis.gamepad.gamepad_event;
import apis.gamepad.gamepad_private;

import apis.dom.detail;
import apis.dom.window;
import apis.dom.window_private;

import apis.hr_time.detail;

import ext.core;
import js.env.realms;


auto gamepad::detail::init() -> void
{
    using namespace std::literals;
    auto e = js::env::env::current();
    hook->set_plug_and_play(true, 100ms);

    hook->set_connect_event_handler([e](std::shared_ptr<::gamepad::device> device)
    {
        // Cannot connect a gamepad to a non-existent Document or a Document which isn't fully active, so if either of
        // those cases are true, return from the event handler staright away.
        decltype(auto) document = e.cpp.global<dom::window*>()->d_func()->document.get();
        if (document && dom::detail::allowed_to_use(document, u"gamepad") == permissions::detail::DENIED)
            return;

        // Create a the task that will be queueud on the gamepad task source.
        auto task = [device]
        {
            // Create a new Gamepad object and get it's relevant javascript environment. Set the 'gamepad's private
            // class's 'platform_device' to the new device that is being connected.
            auto gamepad = std::make_unique<class gamepad>();
            auto relevant_environment = js::env::env::relevant(gamepad.get());
            gamepad->d_func()->platform_gamepad = device;
            gamepad->d_func()->axes = device->get_axes() | ranges::views::values;
            gamepad->d_func()->axis_mapping = device->get_axis();
            gamepad->d_func()->axis_minimums = device->get_axis() | ranges::views::transform([] {return -1;});
            gamepad->d_func()->axis_maximums = device->get_axis() | ranges::views::transform([] {return +1;});
            // TODO : button attributes & transformations

            // Get the navigator of the 'gamepad's relevant envuironment, and add the new Gamepad object into the
            // 'Navigator's private class's 'gamepads' list, at the end.
            decltype(auto) navigator = relevant_environment.cpp.global<dom::window*>()->d_func()->navigator.get();
            navigator->d_func()->gamepads.emplace_back(std::move(gamepad));

            // If the 'navigator' 'has_gamepad_gestures', then set the 'gamepads' privatre class's 'exposed' to True,
            // and fire a "gamepadconnect" event at the 'gamepad's relevant global object, if the document is still
            // fully active.
            if (navigator->d_func()->has_gamepad_gestures)
            {
                gamepad->d_func()->exposed = true;
                if (document && dom::detail::is_fully_active(document))
                    dom::detail::fire_event<gamepad_event>(u"gamepadconnect", relevant_environment.cpp.global<dom::window*>(), {{u"gamepad", gamepad.get()}});
            }
        };

        // Queue the task on the gamepad task queue.
        dom::detail::queue_task(html::detail::task_queues::gamepad_task_queue, task);
    });

    hook->set_disconnect_event_handler([e](std::shared_ptr<::gamepad::device> device)
    {
        // Get the Gamepad instance that corresponds to the 'device' by finding the first Gamepad in the Navigator's
        // list of 'gamepads' whose 'platform_gamepad' matches the device.
        decltype(auto) gamepad = *ranges::first_where(
                e.cpp.global<dom::window*>()->d_func()->navigator->d_func()->gamepads,
                [device](auto&& gamepad) {return gamepad->d_func()->platform_gamepad == device;});

        // Create a the task that will be queueud on the gamepad task source.
        auto task = [&gamepad]
        {
            // Get the 'relevant_envuironment' of the 'gamepad', and the document stored in the 'relevant_environment's
            // private class (Window).
            auto relevant_environment = js::env::env::relevant(gamepad.get());
            decltype(auto) document = relavent_environment.cpp.global<dom::window*>()->d_func()->document.get();

            // Set the 'gamepad's private 'connected' attribute to False (needs to be amrked as not connected if it's
            // going to disocnnect), and fire a "gaemapddisconnect" event atv the 'dcument' if it's not null and is
            // fully active.
            gamepad->d_func()->connected = false;
            if (gamepad->d_func()->exposed && document && dom::detail::is_fully_active(document))
                dom::detail::fire_event<gamepad_event>(u"gamepaddisconnect", relevant_environment.cpp.global<dom::window*>(), {{u"gamepad", gamepad.get()}});

            // Get the Navugatir 'navigatyor' object fromt he 'relevant_envionrment', and set the gamepad in the list to
            // nullptr.
            decltype(auto) navigator = relevant_environment.cpp.global<dom::window*>()->d_func()->navigator;
            *ranges::find(navigator->d_func()->gamepads, gamepad, std::unique_ptr<gamepad>::get) = nullptr;

            // Remove nullptrs from the end of the 'navigator's list of Gamepad objects.
            navigator->d_func()->gamepads |= ranges::actions::rtrim([](auto&& gamepad) {gamepad == nullptr});
        };
    });

    hook->
}


auto gamepad::detail::update_gamepad_state(gamepad* gamepad) -> void
{
    auto e = js::env::env::relevant(gamepad);

    auto now = hr_time::detail::current_hr_time(e.js.global());
    gamepad->d_func()->timestamp = now;

    map_and_normalize_axes(gamepad);
    map_and_normalize_buttons(gamepad);

    decltype(auto) global_object = e.cpp.global<dom::window*>();
    decltype(auto) navigator = global_object->d_func()->navigator.get();

    if (!navigator->d_func()->has_gamepad_gesture() && gamepad->d_func()->contains_gamepad_user_gesture())
    {
        navigator->d_func()->has_gamepad_gesture = true;
        for (decltype(auto) connected_gamepad: navigator->d_func()->gamepads | ranges::views::remove_null)
        {
            connected_gamepad->d_func()->exposed = true;
            connected_gamepad->d_func()->timestamp = now;

            decltype(auto) document = global_object->d_func()->document.get();
            continue_if (!document || !dom::detail::is_document_fully_active(document));
            dom::detail::queue_task(html::detail::task_queues::gamepad_task_source,
                    [gamepad, &e]
                    {dom::detail::fire_event<gamepad_event>(u"gamepadconnected", e.js.global(), {{u"gamepad", gamepad}});});
        }
    }
}


auto gamepad::detail::map_and_normalize_axes(gamepad* gamepad) -> void
{
    decltype(auto) axis_values = gamepad->d_func()->axes;

    for (auto raw_axis_index = 0; raw_axis_index < axis_values.size(); ++raw_axis_index)
    {
        auto mapped_index = gamepad->d_func()->axis_mapping[raw_axis_index];
        auto logical_value = axis_values[raw_axis_index];
        auto logical_minimum = gamepad->d_func()->axis_minimums[raw_axis_index];
        auto logical_maximum = gamepad->d_func()->axis_maximums[raw_axis_index];

        auto normalized_value = 2.0 * (logical_value - logical_minimum) / (logical_maximum - logical_minimum) - 1;
        gamepad->d_func()->axes[raw_axis_index] = std::move(normalized_value);
    }
}


auto gamepad::detail::map_and_normalize_buttons(gamepad* gamepad) -> void
{
    decltype(auto) button_values = gamepad->d_func()->buttons | ranges::views::transform_to_attr(&gamepad_button_private::value, ext::get_pimpl);

    for (auto raw_button_index = 0; raw_button_index < button_values.size(); ++raw_button_index)
    {
        auto mapped_index = gamepad->d_func()->button_mapping[raw_button_index];
        auto logical_value = button_values[raw_button_index] ;
        auto logical_minimum = gamepad->d_func()->button_minimums[raw_button_index];
        auto logical_maximum = gamepad->d_func()->button_maximums[raw_button_index];

        auto normalized_value = 2.0 * (logical_value - logical_minimum) / (logical_maximum - logical_minimum) - 1;
        decltype(auto) button = gamepad->d_func()->buttons[mapped_index];
        button.d_func()->value = std::move(normalized_value);

        // TODO: button->s_pressed, button->s_touched
    }
}

