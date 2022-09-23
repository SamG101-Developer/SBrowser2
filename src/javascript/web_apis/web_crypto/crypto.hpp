#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO_CRYPTO_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO_CRYPTO_HPP

#include "dom_object.hpp"
namespace web_crypto {class crypto;}

namespace web_crypto {class subtle_crypto;}


class web_crypto::crypto
        : public virtual dom_object
{
public constructors:
    crypto() = default;

public js_methods:
    auto get_random_values(v8::Local<v8::ArrayBufferView> array) -> v8::Local<v8::ArrayBufferView>;
    auto random_uuid() -> ext::string;

private js_properties:
    ext::property<std::unique_ptr<subtle_crypto>> subtle;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO_CRYPTO_HPP
