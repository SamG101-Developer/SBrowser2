#ifndef SBROWSER2_SRC_EXT_INITIALIZER_LIST_HPP
#define SBROWSER2_SRC_EXT_INITIALIZER_LIST_HPP

#include <initializer_list>
#include "ext/keywords.hpp"


_EXT_BEGIN


template <typename T>
struct initializer_list
{
public:
    constexpr operator std::initializer_list<T>() const {return m_list;}

private:
    std::initializer_list<T> m_list;
};


template <typename T>
auto make_initializer_list_repeat(T&& argument, size_t repeat) -> initializer_list<T>
{
    // TODO
}


template <typename ...Args>
auto make_initializer_list(Args&&... arguments) -> initializer_list<Args...>
{
    // TODO
}


_EXT_END


#endif //SBROWSER2_SRC_EXT_INITIALIZER_LIST_HPP
