#include "subtle_crypto.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(web_crypto)



#include "web_crypto/crypto_key.hpp"
#include "web_crypto/detail/crypto_internals.hpp"



auto web_crypto::subtle_crypto::encrypt(
        detail::algorithm_identifier_t algorithm,
        web_crypto::crypto_key* key,
        v8::Local<v8::BufferSource> data)
        -> ext::promise<ext::any>
{
    detail::common_crypto(algorithm, key, data, detail::key_usage_t::ENCRYPT);
}


auto web_crypto::subtle_crypto::decrypt(
        detail::algorithm_identifier_t algorithm,
        web_crypto::crypto_key* key,
        v8::Local<v8::BufferSource> data)
        -> ext::promise<ext::any>
{
    detail::common_crypto(algorithm, key, data, detail::key_usage_t::DECRYPT);
}


auto web_crypto::subtle_crypto::sign(
        detail::algorithm_identifier_t algorithm,
        web_crypto::crypto_key* key,
        v8::Local<v8::BufferSource> data)
        -> ext::promise<ext::any>
{
    detail::common_crypto(algorithm, key, data, detail::key_usage_t::SIGN);
}


auto web_crypto::subtle_crypto::verify(
        detail::algorithm_identifier_t algorithm,
        web_crypto::crypto_key* key,
        v8::Local<v8::BufferSource> signature,
        v8::Local<v8::BufferSource> data)
        -> ext::promise<ext::any>
{
    detail::common_crypto(algorithm, key, data, detail::key_usage_t::VERIFY, signature);
}



