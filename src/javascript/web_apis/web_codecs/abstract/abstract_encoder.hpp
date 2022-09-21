#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_ABSTRACT_ABSTRACT_ENCODER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_ABSTRACT_ABSTRACT_ENCODER_HPP

#include "web_codecs/abstract/abstract_encoder_decoder.hpp"
#include INCLUDE_INNER_TYPES(web_codecs)

namespace web_codecs::abstract {class abstract_encoder;}
namespace web_codecs::audio {class audio_data;}
namespace web_codecs::video {class video_data;}


class web_codecs::abstract::abstract_encoder
        : public abstract_encoder_decoder
{
public constructors:
    DOM_CTORS(abstract_encoder);
    abstract_encoder() = default;
    abstract_encoder(ext::map<ext::string, ext::any>&& init);

public js_methods:
    auto configure(detail::audio_decoder_config_t&& config) -> void;
    virtual auto encode(audio::audio_data* data) -> void {};
    virtual auto encode(video::video_data* data) -> void {};

public js_properties:
    ext::property<ext::number<ulong>> encode_queue_size;

protected js_slots:
    ext::slot<ext::number<ulong>> s_encode_queue_size;
    ext::slot<ext::map<ext::string, ext::any>> s_active_encode_config;
    ext::slot<ext::map<ext::string, ext::any>> s_active_output_config;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(encode_queue_size);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_ABSTRACT_ABSTRACT_ENCODER_HPP
