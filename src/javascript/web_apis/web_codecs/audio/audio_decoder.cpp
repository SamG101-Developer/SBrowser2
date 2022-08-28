#include "audio_decoder.hpp"

#include "web_codecs/abstract/abstract_decoder.hpp"


web_codecs::audio::audio_decoder::audio_decoder(
        detail::audio_decoder_init_t&& init)
        : abstract::abstract_decoder{std::move(init)}
{}


auto web_codecs::audio::audio_decoder::decode(
        audio::encoded_audio_chunk* data)
        -> void
{
    abstract::abstract_decoder::decode(data);
}
