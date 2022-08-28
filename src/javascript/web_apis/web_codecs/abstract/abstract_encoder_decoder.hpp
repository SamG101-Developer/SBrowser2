#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_ABSTRACT_ABSTRACT_ENCODER_DECODER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_ABSTRACT_ABSTRACT_ENCODER_DECODER_HPP

#include "dom_object.hpp"
namespace web_codecs::abstract {class abstract_encoder_decoder;}

#include <future>
#include "ext/queue.hpp"
#include USE_INNER_TYPES(web_codecs)


class web_codecs::abstract::abstract_encoder_decoder
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(abstract_encoder_decoder);
    abstract_encoder_decoder() = default;
    abstract_encoder_decoder(ext::map<ext::string, ext::any>&& init);

public js_methods:
    virtual auto configure(detail::audio_decoder_config_t&& config) -> void; // TODO: IMPL
    auto flush() -> std::promise<void>;
    auto reset() -> void;
    auto close() -> void;
    static auto is_config_supported() -> std::promise<detail::audio_decoder_support_t>;

public js_properties:
    ext::property<detail::codec_state_t> state;

protected js_slots:
    ext::slot<ext::queue<detail::control_message_t>> s_control_message_queue;
    ext::slot<ext::boolean> s_message_queue_blocked;
    ext::slot<ext::any> s_codec_implementation; // TODO: type
    ext::slot<ext::queue<ext::any>> s_codec_work_queue; // TODO: type
    ext::slot<ext::boolean> s_codec_saturated;
    ext::slot<ext::function<void()>> s_output_callback;
    ext::slot<ext::function<void()>> s_error_callback;
    ext::slot<detail::codec_state_t> s_state;
    ext::slot<ext::vector<std::promise<void>>> s_pending_flush_promise;
    ext::slot<ext::boolean> s_dequeue_event_scheduled;

private cpp_accessors:
    DEFINE_GETTER(state) {return s_state();}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_ABSTRACT_ABSTRACT_ENCODER_DECODER_HPP
