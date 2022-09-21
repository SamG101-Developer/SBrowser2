#include "abstract_decoder.hpp"

#include INCLUDE_INNER_TYPES(web_codecs)
#include "dom/detail/event_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "web_codecs/detail/algorithm_internals.hpp"


web_codecs::abstract::abstract_decoder::abstract_decoder(
        ext::map<ext::string, ext::any>&& init)
        : abstract_encoder_decoder{std::move(init)}
        , s_key_chunk_required{true}
        , s_decode_queue_size{0}
        , s_active_decode_config{std::move(init)}
{}


auto web_codecs::abstract::abstract_decoder::set_decode_queue_size(
        const decltype(decode_queue_size)::value_t& val)
        -> void
{
    dom::detail::fire_event("deque", this);
    guard_property(decode_queue_size);
    *decode_queue_size = val;
}


auto web_codecs::abstract::abstract_decoder::decode(
        abstract_encoded_chunk* chunk) -> void
{
    dom::detail::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [this] {s_state = detail::codec_state_t::CLOSED;},
            "Cannot configure a closed encoder or decoder");

    if (s_key_chunk_required)
    {
        dom::detail::throw_v8_exception<V8_DATA_ERROR>(
                [this, chunk] {return chunk->s_type != detail::encoded_audio_chunk_type_t::KEY;},
                "Cannot configure a closed encoder or decoder");

        // TODO : inspect chunk->s_internal_data
        s_key_chunk_required = false;
    }

    decode_queue_size += 1;
    detail::enqueue_control_message(this);
    detail::process_control_message_queue(this);
}
