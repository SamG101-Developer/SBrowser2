#pragma once
#ifndef SBROWSER2_META_PROPERTY_HPP
#define SBROWSER2_META_PROPERTY_HPP

#include "ext/functional.hpp"

namespace ext {template <typename ...Ts> class property;}
namespace ext::detail {template <typename T> class meta_property;}
namespace ext::detail {class lockable;}
struct access_meta;


template <typename T>
class ext::detail::meta_property
{
public:
    friend struct ::access_meta;
    friend struct property<T>;

    using value_t = T;
    using getter_t = ext::function<value_t() const>;
    using setter_t = ext::function<value_t(value_t)>;
    using deleter_t = ext::function<void()>;

private:
    value_t m_value;
    getter_t m_getter = [this] {return m_value;};
    setter_t m_setter = [this](value_t&& val) {return m_value = std::forward<value_t>(val);};
    deleter_t m_deleter = [] {};
};


template <typename T>
class ext::detail::meta_property<std::unique_ptr<T>>
{
public:
    friend struct ::access_meta;
    friend struct property<std::unique_ptr<T>>;

    using value_t = typename std::unique_ptr<T>::pointer;
    using getter_t = ext::function<value_t() const>;
    using setter_t = ext::function<value_t(value_t)>;
    using deleter_t = ext::function<void()>;

private:
    std::unique_ptr<T> m_value;
    getter_t m_getter = [this] {return m_value.get();};
    setter_t m_setter = [this](value_t&& val) {m_value.reset(std::forward<value_t>(val)); return m_value.get();};
    deleter_t m_deleter = [] {};
};


struct ext::detail::lockable
{
public:
    auto lock() -> void
    {m_locked = true;}

    auto unlock() -> void
    {m_locked = false;}

protected:
    bool m_locked = true;
};

#endif //SBROWSER2_META_PROPERTY_HPP
