#include "abstract_encoder_decoder.hpp"

#include USE_INNER_TYPES(dom)
#include USE_INNER_TYPES(web_codecs)

#include "dom/detail/exception_internals.hpp"
#include "dom/other/dom_exception.hpp"

#include "web_codecs/abstract/abstract_decoder.hpp"
#include "web_codecs/detail/algorithm_internals.hpp"


web_codecs::abstract::abstract_encoder_decoder::abstract_encoder_decoder(
        ext::map<ext::string, ext::any>&& init)
        : s_control_message_queue{ext::queue<ext::function<void()>>{}}
        , s_message_queue_blocked{false}
        , s_codec_implementation{nullptr}
        , s_codec_work_queue{ext::queue<ext::any>{}}
        , s_codec_saturated{false}
        , s_output_callback{init.try_emplace("output").first->second.to<decltype(s_output_callback)::value_t>()}
        , s_error_callback{init.try_emplace("error").first->second.to<decltype(s_error_callback)::value_t>()}
        , s_state{detail::codec_state_t::UNCONFIGURED}
        , s_pending_flush_promise{ext::vector<std::promise<void>>{}}
        , s_dequeue_event_scheduled{false}
{}


auto web_codecs::abstract::abstract_encoder_decoder::configure(
        detail::audio_decoder_config_t&& config)
        -> void
{
    dom::detail::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [this] {s_state = detail::codec_state_t::CLOSED;},
            "Cannot configure a closed encoder or decoder");

    s_state = detail::codec_state_t::CONFIGURED;
    if (decltype(auto) decoder = dynamic_cast<abstract_decoder*>(this))
        decoder->s_key_chunk_required = true;

    detail::queue_control_message(this, ext::bind_front{detail::run_control_message_config, this});
    detail::process_control_message_queue(this);
}


auto web_codecs::abstract::abstract_encoder_decoder::flush()
        -> std::promise<void>
{
    std::promise<void> promise;

    if (s_state() != detail::codec_state_t::CONFIGURED)
    {
        promise.set_exception(dom::other::dom_exception{"Cannot configure a closed encoder or decoder", INVALID_STATE_ERR});
        return promise;
    }

    s_pending_flush_promise().push_back(std::move(promise));
    detail::queue_control_message(this, ext::bind_front{detail::run_control_message_flush, this, std::move(promise)});
    detail::process_control_message_queue(this);

    return promise;
}
