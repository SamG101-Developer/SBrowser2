#include "constrainable.hpp"
#include "constrainable_private.hpp"

#include "ext/casting.hpp"

#include "mediacapture_main/_typedefs.hpp"
#include "mediacapture_main/media_stream_track.hpp"
#include "mediacapture_main/media_stream_track_private.hpp"
#include "mediacapture_main/detail/constrain_internals.hpp"

#include "ext/promise.hpp"


auto mediacapture::main::mixins::constrainable::get_capabilities() const -> detail::capabilities_t
{
    // get the data in the [[capabilities]] internal slot
    ACCESS_PIMPL(const constrainable);
    return d->capabilities;
}


auto mediacapture::main::mixins::constrainable::get_constraints() const -> detail::constraints_t
{
    // get the data in the [[constraints]] internal slot
    ACCESS_PIMPL(const constrainable);
    return d->constraints;
}


auto mediacapture::main::mixins::constrainable::get_settings() const -> detail::settings_t
{
    // get the base MediaStreamTrack object from this mixin
    ACCESS_PIMPL(const constrainable);
    decltype(auto) base = dom_cross_cast<const main::media_stream_track*>(this);

    // if the track has ended, then return a dictionary containing certain properties, otherwise return the data in the
    // [[settings]] internal slot
    return base->d_func()->ready_state == detail::media_stream_track_state_t::ENDED
            ? ext::map<ext::string, ext::any>{
                {u"deviceId", base->d_func()->device_id},
                {u"facingMode", base->d_func()->facing_mode},
                {u"groupId", base->d_func()->group_id}}
            : d->settings;
}


auto mediacapture::main::mixins::constrainable::apply_constraints(detail::constraints_t&& constraints) -> ext::promise<void>
{
    // get the base MediaStreamTrack object from this mixin
    decltype(auto) base = dom_cross_cast<const main::media_stream_track*>(this);

    if (base->d_func()->ready_state == detail::media_stream_track_state_t::ENDED)
    {
        auto promise = ext::promise<void>{};
        promise.resolve();
        return promise;
    }

    return detail::apply_constrains_template_algorithm(this);
}


auto mediacapture::main::mixins::constrainable::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<constrainable>{isolate}
        .inherit<dom_object>()
        .function("getCapabilities", &constrainable::get_capabilities)
        .function("getConstraints", &constrainable::get_constraints)
        .function("getSettings", &constrainable::get_settings)
        .auto_wrap_objects();

    return std::move(conversion);
}
