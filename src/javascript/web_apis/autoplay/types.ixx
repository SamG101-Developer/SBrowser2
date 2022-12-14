export module apis.autoplay.types;


export namespace autoplay::detail
{
    enum class autoplay_policy_t {ALLOWED, ALLOWED_MUTED, DISALLOWED};
    enum class autoplay_policy_media_type_t {MEDIA_ELEMENT, AUDIO_CONTEXT};
}
