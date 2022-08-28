#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_DETAIL_ALGORITHM_INTERNALS_HPP

namespace dom::other {class dom_exception;}
namespace web_codecs::abstract {class abstract_encoder_decoder;}
namespace web_codecs::abstract {class abstract_encoder;}
namespace web_codecs::abstract {class abstract_decoder;}
namespace web_codecs::audio {class audio_decoder;}

namespace web_codecs::detail
{
    auto schedule_dequeue_event(
            audio::audio_decoder* audio_decoder)
            -> void;

    template <typename ...Args>
    auto output_audio_data(
            audio::audio_decoder* audio_decoder,
            Args&&... outputs)
            -> void;

    auto reset_audio_decoder(
            audio::audio_decoder* audio_decoder,
            dom::other::dom_exception& exception)
            -> void;

    auto close_audio_Decoder(
            audio::audio_decoder* audio_decoder,
            dom::other::dom_exception& exception)
            -> void;

    template <typename F>
    auto queue_control_message(
            abstract::abstract_encoder_decoder* decoder,
            F&& method)
            -> void;

    auto run_control_message_config(
            abstract::abstract_encoder_decoder* decoder)
            -> void;

    auto run_control_message_decode(
            abstract::abstract_decoder* decoder)
            -> void;

    auto run_control_message_encode(
            abstract::abstract_encoder* encoder)
            -> void;

    auto run_control_message_flush(
            abstract::abstract_encoder_decoder* decoder)
            -> void;

    auto process_control_message_queue(
            abstract::abstract_encoder_decoder* decoder)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_DETAIL_ALGORITHM_INTERNALS_HPP
