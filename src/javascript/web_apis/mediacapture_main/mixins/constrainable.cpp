#include "constrainable.hpp"

#include "ext/casting.hpp"

#include "dom_object.hpp"
#include "mediacapture_main/media_stream_track.hpp"
#include "mediacapture_main/details/constrain_internals.hpp"

#include <future>


auto mediacapture::main::mixins::constrainable::get_capabilities()
        const -> detail::capabilities_t
{
    // get the data in the [[capabilities]] internal slot
    return s_capabilities;
}


auto mediacapture::main::mixins::constrainable::get_constraints()
        const -> detail::constraints_t
{
    // get the data in the [[constraints]] internal slot
    return s_constraints;
}


auto mediacapture::main::mixins::constrainable::get_settings()
        const -> detail::settings_t
{
    // get the base MediaStreamTrack object from this mixin
    auto* base = dom_cross_cast<const main::media_stream_track*>(this);

    // if the track has ended, then return a dictionary containing certain properties, otherwise return the data in the
    // [[settings]] internal slot
    return base->ready_state() == "ended"
            ? ext::map<ext::string, ext::any>{
                {"deviceId", base->device_id()},
                {"facingMode", base->facing_mode()},
                {"groupId", base->group_id()}}
            : s_settings;
}


auto mediacapture::main::mixins::constrainable::apply_constraints(
        detail::constraints_t&& constraints)
        -> std::promise<void>
{
    // get the base MediaStreamTrack object from this mixin
    auto* base = dom_cross_cast<const main::media_stream_track*>(this);

    if (base->ready_state() == "ended")
    {
        std::promise<void> promise;
        promise.set_value();
        return promise;
    }

    return detail::constrain_internals::apply_constrains_template_algorithm(this);
}


auto mediacapture::main::mixins::constrainable::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<constrainable>{isolate}
            .inherit<dom_object>()
            .function("getCapabilities", &constrainable::get_capabilities)
            .function("getConstraints", &constrainable::get_constraints)
            .function("getSettings", &constrainable::get_settings)
            .slot("capabilities", &constrainable::s_capabilities)
            .slot("constraints", &constrainable::s_constraints)
            .slot("settings", &constrainable::s_settings)
            .auto_wrap_objects();
}
