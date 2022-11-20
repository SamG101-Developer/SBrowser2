#include "serialization_internals.hpp"


template <html::concepts::is_serializable T>
auto html::detail::structured_clone(T* value) -> std::unique_ptr<T>
{
    auto clone = std::make_unique<T>();
    auto serialization = ext::map<ext::string, ext::any>{};
    value->_serialize(serialization);
    clone->_deserialize(std::move(serialization));
    return clone;
}
