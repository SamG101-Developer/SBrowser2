#include "media_session.hpp"
#include "media_session_private.hpp"






#include "html/navigators/navigator.hpp"
#include "html/navigators/navigator_private.hpp"

#include "mediasession/detail/media_session_internals.hpp"
#include "mediasession/media_metadata.hpp"
#include "mediasession/media_metadata_private.hpp"


auto mediasession::media_session::set_action_handler(
        detail::media_session_action_t action,
        detail::media_session_action_handler_t&& handler)
        -> void
{
    detail::update_action_handler(this, action, std::move(handler));
}


auto mediasession::media_session::set_position_state(
        detail::media_position_state_t&& state)
        -> void
{
    ACCESS_PIMPL(media_session);
    using enum v8_primitive_error_t;
    auto e = js::env::env::relevant(this);

    if (state.empty())
        ; // TODO

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&state] {return !state.contains(u"duration") || state[u"duration"] < 0.0;},
            "Must provide a non-null, non-negative duration", e);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&state] {return !state.contains(u"position") || state[u"position"] < 0.0 || state[u"position"] > state[u"duration"];},
            "Must provide a non-null, non-negative position that is smaller than the duration", e);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&state] {return state[u"playbackRate", 1.0] != 0.0;},
            "Must provide a non-zero playbackRate", e);
}


auto mediasession::media_session::get_metadata() const -> media_metadata*
{
    ACCESS_PIMPL(const media_session);
    return d->metadata.get();
}


auto mediasession::media_session::get_playback_state() const -> detail::media_session_playback_state_t
{
    ACCESS_PIMPL(const media_session);
    return d->state;
}


auto mediasession::media_session::set_metadata(
        media_metadata* new_metadata)
        -> media_metadata*
{
    ACCESS_PIMPL(media_session);
    if (d->metadata) d->metadata->d_func()->media_session = nullptr;
    d->metadata.reset(new_metadata);
    if (d->metadata) d->metadata->d_func()->media_session = this;
    GO &detail::update_metadata;
}


auto mediasession::media_session::set_playback_state(
        detail::media_session_playback_state_t new_playback_state)
        -> detail::media_session_playback_state_t
{
    ACCESS_PIMPL(media_session);
    return d->state = new_playback_state;
}


auto mediasession::media_session::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .function("setActionHandler", &media_session::set_action_handler)
        .function("setPositionState", &media_session::set_position_state)
        .function("setMicrophoneActive", &media_session::set_microphone_active)
        .function("setCameraActive", &media_session::set_camera_active)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
