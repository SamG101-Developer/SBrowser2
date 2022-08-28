#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_ABSTRACT_ABSTRACT_DECODER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_ABSTRACT_ABSTRACT_DECODER_HPP

#include "web_codecs/abstract/abstract_encoder_decoder.hpp"
namespace web_codecs::abstract {class abstract_decoder;}
namespace web_codecs::abstract {class abstract_encoded_chunk;}


class web_codecs::abstract::abstract_decoder
        : public abstract_encoder_decoder
{
public constructors:
    DOM_CTORS(abstract_decoder);
    abstract_decoder() = default;
    abstract_decoder(ext::map<ext::string, ext::any>&& init);

protected js_methods:
    virtual auto decode(abstract_encoded_chunk* chunk) -> void {};

public js_properties:
    ext::property<ext::number<ulong>> decode_queue_size;

protected js_slots:
    ext::slot<ext::boolean> s_key_chunk_required;
    ext::slot<ext::number<ulong>> s_decode_queue_size;
    ext::slot<ext::map<ext::string, ext::any>> s_active_decode_config;

private cpp_accessors:
    DEFINE_SETTER(decode_queue_size);
    DEFINE_GETTER(decode_queue_size) {return s_decode_queue_size();}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CODECS_ABSTRACT_ABSTRACT_DECODER_HPP
