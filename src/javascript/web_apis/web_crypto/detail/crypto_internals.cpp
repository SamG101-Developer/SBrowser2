#include "crypto_internals.hpp"

#include "ext/custom_operator.hpp"
#include "javascript/interop/annotations.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(web_crypto)

#include "dom/detail/exception_internals.hpp"

#include "web_crypto/crypto_key.hpp"

#include <v8-array-buffer.h>
#include <v8-exception.h>

#include <range/v3/algorithm/contains.hpp>


template <typename ...Args>
auto web_crypto::detail::common_crypto(
        detail::algorithm_identifier_t algorithm,
        web_crypto::crypto_key* key,
        v8::Local<v8::BufferSource> data,
        detail::key_usage_t usage,
        Args&&... args)
        -> ext::promise<ext::any>
{
    JS_EXCEPTION_HANDLER;
    auto promise = ext::promise<ext::any>{};
    auto copy_data = ext::string{data->ByteLength()};
    auto normalized_algorithm = detail::normalize_algorithm(algorithm, usage);
    data->CopyContents(&copy_data, data->ByteLength());

    return_if (JS_EXCEPTION_HAS_THROWN) promise.reject(JS_EXCEPTION);

    GO [key, usage, &promise, &normalized_algorithm] mutable
    {
        JS_EXCEPTION_HANDLER;

        dom::detail::throw_v8_exception_formatted<INVALID_ACCESS_ERR>(
                [key, &normalized_algorithm] {return normalized_algorithm["name"].to<detail::algorithm_identifier_t>() != key->s_algorithm();},
                "Name mismatch");

        dom::detail::throw_v8_exception_formatted<INVALID_ACCESS_ERR>(
                [key, usage] {return !ranges::contains(key->s_usages(), usage);},
                "Key cannot be used for encryption");

        if (JS_EXCEPTION_HAS_THROWN)
            promise.reject(JS_EXCEPTION);

        // TODO: apply algorithm (+arguments) and resolve promise
    };

    return promise;
}
