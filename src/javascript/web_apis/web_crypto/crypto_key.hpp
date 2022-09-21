#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO_CRYPTO_KEY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO_CRYPTO_KEY_HPP

#include "dom_object.hpp"
#include "html/mixins/serializable.hpp"
namespace web_crypto {class crypto_key;}

#include INCLUDE_INNER_TYPES(web_crypto)


class web_crypto::crypto_key
        : public virtual dom_object
        , public html::mixins::serializable
{
public constructors:
    crypto_key() = default;

public js_properties:
    ext::property<detail::key_type_t> type;
    ext::property<ext::boolean> extractable;
    ext::property<void*> algorithm;
    ext::property<ext::vector<detail::key_usage_t>> usages;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
    auto m_serialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> void override;
    auto m_deserialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> crypto_key* override;

private js_slots:
    ext::slot<detail::key_type_t> s_type;
    ext::slot<ext::boolean> s_extractable;
    ext::slot<detail::algorithm_identifier_t> s_algorithm;
    ext::slot<detail::algorithm_identifier_t> s_algorithm_cached;
    ext::slot<ext::vector<detail::key_usage_t>> s_usages;
    ext::slot<ext::vector<detail::key_usage_t>> s_usages_cached;
    ext::slot<void*> s_handle;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(type) {return s_type();}
    DEFINE_CUSTOM_GETTER(extractable) {return s_extractable();}
    DEFINE_CUSTOM_GETTER(algorithm);
    DEFINE_CUSTOM_GETTER(usages);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_CRYPTO_CRYPTO_KEY_HPP
