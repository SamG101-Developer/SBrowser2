#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO_SUBTLE_CRYPTO_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO_SUBTLE_CRYPTO_HPP

#include "dom_object.hpp"
namespace web_crypto {class subtle_crypto;}



#include INCLUDE_INNER_TYPES(web_crypto)
#include INCLUDE_INNER_TYPES(web_idl)
namespace web_crypto {class crypto_key;}


class web_crypto::subtle_crypto
        : public virtual dom_object
{
public constructors:
    subtle_crypto() = default;

public js_methods:
    auto encrypt(detail::algorithm_identifier_t algorithm, crypto_key* key, v8::Local<v8::BufferSource> data) -> ext::promise<ext::any>;
    auto decrypt(detail::algorithm_identifier_t algorithm, crypto_key* key, v8::Local<v8::BufferSource> data) -> ext::promise<ext::any>;
    auto sign(detail::algorithm_identifier_t algorithm, crypto_key* key, v8::Local<v8::BufferSource> data) -> ext::promise<ext::any>;
    auto verify(detail::algorithm_identifier_t algorithm, crypto_key* key, v8::Local<v8::BufferSource> signature, v8::Local<v8::BufferSource> data) -> ext::promise<ext::any>;
    auto digest(detail::algorithm_identifier_t algorithm, v8::Local<v8::BufferSource> data) -> ext::promise<ext::any>;

    auto generate_key(detail::algorithm_identifier_t algorithm, ext::boolean extractable, ext::vector_view<detail::key_usage_t> key_usages) -> ext::promise<ext::any>;
    auto derive_key(detail::algorithm_identifier_t algorithm, crypto_key* base_key, detail::algorithm_identifier_t derived_key_type, ext::boolean extractable, ext::vector_view<detail::key_usage_t> key_usages) -> ext::promise<ext::any>;
    auto derive_bits(detail::algorithm_identifier_t algorithm, crypto_key* base_key, ext::number<ulong> length) -> ext::promise<ext::any>;

    auto import_key(detail::key_format_t key_format, v8::Local<v8::BufferSource> key_data, detail::algorithm_identifier_t algorithm, ext::boolean extrsctable, ext::vector_view<detail::key_usage_t> key_usages) -> ext::promise<crypto_key*>;
    auto expose_key(detail::key_format_t key_format, crypto_key* key) -> ext::promise<ext::any>;
    auto wrap_key(detail::key_format_t key_foramt, crypto_key* key, crypto_key* wrapping_key, detail::algorithm_identifier_t wrap_algorithm) -> ext::promise<ext::any>;
    auto unwrap_key(detail::key_format_t format, v8::Local<v8::BufferSource> wrapped_key, crypto_key* key, detail::algorithm_identifier_t unwrap_algorithm, detail::algorithm_identifier_t unwrapped_key_algorithm, ext::boolean extractable, ext::vector<detail::key_usage_t> key_usages) -> ext::promise<crypto_key*>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO_SUBTLE_CRYPTO_HPP
