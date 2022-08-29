#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_AUDIO_AUDIO_DECODER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_AUDIO_AUDIO_DECODER_HPP

#include "web_codecs/abstract/abstract_decoder.hpp"
namespace web_codecs::audio {class audio_decoder;}

#include "ext/promise.hpp"
#include "ext/queue.hpp"
#include USE_INNER_TYPES(web_codecs)
namespace web_codecs::audio {class encoded_audio_chunk;}


class web_codecs::audio::audio_decoder
        : public abstract::abstract_decoder
{
public constructors:
    DOM_CTORS(audio_decoder);
    audio_decoder() = default;
    audio_decoder(detail::audio_decoder_init_t&& init);

public js_methods:
    auto decode(audio::encoded_audio_chunk* data) -> void override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_AUDIO_AUDIO_DECODER_HPP
