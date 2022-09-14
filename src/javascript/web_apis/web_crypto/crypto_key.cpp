#include "crypto_key.hpp"


auto web_crypto::crypto_key::m_serialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage)
        -> void
{
    serialized.emplace("$Type", s_type());
    serialized.emplace("$Extractable", s_extractable());
    serialized.emplace("$Algorithm", ext::holds_alternative<ext::string>(s_algorithm()) ? ext::get<ext::string>(s_algorithm()) : ext::get<void*>(s_algorithm())->m_serialize());
    serialized.emplace("$Usages", ext::to_string(s_usages()));
    serialized.emplace("$Handle", s_handle());
}


auto web_crypto::crypto_key::m_deserialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage) -> crypto_key*
{
    s_type = serialized["$Type"].to<decltype(s_type)::value_t>();
    s_extractable = serialized["$Extractable"].to<decltype(s_extractable)::value_t>();
    s_algorithm = serialized["$Algorithm"].to<decltype(s_algorithm)::value_t>();
    s_usages = serialized["$Usages"].to<decltype(s_usages)::value_t>();
    s_handle = serialized["$Handle"].to<decltype(s_handle)::value_t>();
}
