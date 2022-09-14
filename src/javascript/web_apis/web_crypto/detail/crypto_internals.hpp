#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO_DETAIL_CRYPTO_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO_DETAIL_CRYPTO_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/promise.hpp"
#include "ext/slot.hpp"
#include <v8-forward.h>

#include USE_INNER_TYPES(web_crypto)
#include USE_INNER_TYPES(web_idl)

namespace web_crypto {class crypto_key;}


namespace web_crypto::detail
{
    template <typename ...Args>
    auto common_crypto(
            detail::algorithm_identifier_t algorithm,
            web_crypto::crypto_key* key,
            v8::Local<v8::BufferSource> data,
            detail::key_usage_t usage,
            Args&&... args)
            -> ext::promise<ext::any>;

    template <typename T>
    auto cached_ecmascript_object(
            const ext::slot<T>& slot,
            const ext::slot<T>& slot_cached)
            -> T;

    auto normalize_algorithm(
            detail::algorithm_identifier_t algorithm,
            detail::key_usage_t operation)
            -> ext::map<ext::string, ext::any>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO_DETAIL_CRYPTO_INTERNALS_HPP
