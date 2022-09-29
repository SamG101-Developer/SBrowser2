#ifndef SBROWSER2_SRC_EXT_MEMORY_HPP
#define SBROWSER2_SRC_EXT_MEMORY_HPP

#include "ext/concepts.hpp"


_EXT_BEGIN

template <callable F, typename ...Args>
auto make_unique_from_factory(F&& factory_method, Args&&... args)
{
    auto object = factory_method(std::forward<Args>(args)...);
    return std::unique_ptr{&object};
}

_EXT_END


#endif //SBROWSER2_SRC_EXT_MEMORY_HPP
