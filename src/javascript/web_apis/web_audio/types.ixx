export module apis.web_audio.types;


export namespace web_audio::detail
{
    enum class audio_context_state_t {SUSPEND, RUNNING, CLOSED};
    enum class audio_context_latency_category_t {BALANCED, INTERACTIVE, PLAYBACK};
    enum class audio_sink_type_t {NONE};
}
