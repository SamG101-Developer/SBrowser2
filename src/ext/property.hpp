#pragma once
#ifndef SBROWSER2_PROPERTY_HPP
#define SBROWSER2_PROPERTY_HPP

#include <memory>
#include "ext/streams.hpp"
#include "ext/detail/meta_property.hpp"
namespace ext {template <typename T> class property;}


/**
 * Property class for specialized for the std::unique_ptr<T> type. Differences include how the copy constructor and
 * dereference operator work (std::unique_ptr<T> can not be copied)
 * @tparam T Underlying type in the std::unique_ptr<T> of the property
 */
template <typename T>
class ext::property<std::unique_ptr<T>>: private detail::lockable
{
public:
    // Access to the value type (std::unique_ptr<T>'s pointer type)
    friend struct ::access_meta;
    using value_t = typename std::unique_ptr<T>::pointer;

    // Default constructor
    property() = default;

    // Copy constructor (involves the unique_ptr semantics)
    property(const property& other)
    {
        m_meta.m_getter = other.m_meta.m_getter;
        m_meta.m_setter = other.m_meta.m_setter;
        m_meta.m_deleter = other.m_meta.m_deleter;
        m_meta.m_value.reset(other.m_meta.m_value.get());
    }

    // Move constructor
    property(property&& other) noexcept
    {
        m_meta.m_getter = std::move(other.m_meta.m_getter);
        m_meta.m_setter = std::move(other.m_meta.m_setter);
        m_meta.m_deleter = std::move(other.m_meta.m_deleter);
        m_meta.m_value = std::move(other.m_meta.m_value);
    }

    // Copy value constructor
    explicit property(const value_t& other)
    {m_meta.m_value.reset(other);}

    // Move value constructor
    explicit property(value_t&& other)
    {m_meta.m_value.reset(std::move(other));}

    // Special nullptr_t constructor
    explicit property(std::nullptr_t&&)
    {m_meta.m_value = nullptr;}

    // Destructor calls the deleter
    ~property()
    {m_meta.m_deleter();}

    // Delete assignment operators (prevent accidental copying instead of setting value with operator()() from another
    // property)
    auto operator=(const property&) -> property& = delete;
    auto operator=(property&&) noexcept -> property& = delete;

    // Getter and setter operators for the property (because T is a std::unique_ptr<T>, a raw pointer is used as the
    // type of variable for the setter's parameter and the getters return type
    auto operator()() const -> decltype(auto) {return m_meta.m_getter();}
    auto operator=(const value_t& value) -> value_t {return m_meta.m_setter(value);}
    auto operator=(value_t&& value) -> value_t {return m_meta.m_setter(std::move(value));}

    // Dereferencing accesses the inner value type of the property (for custom getters and setters), so move the
    // std::unique_ptr out of the meta property to the return value. Check the property is unlocked before accessing the
    // internal value
    auto operator*() -> auto&& {assert(!m_locked); return std::move(m_meta.m_value);}
    auto operator*() const -> const auto&& {assert(!m_locked); return std::move(m_meta.m_value);}

private:
    detail::meta_property<std::unique_ptr<T>> m_meta;
};


/**
 * Property class for basic type T (non-specialized). It contain teh copy and move semantics, the setting and getting of
 * the value inside the property, and the dereferencing
 * @tparam T Underlying type of the property
 */
template <typename T>
class ext::property : private detail::lockable
{
public:
    // Access to the value type
    friend struct ::access_meta;
    using value_t = T;

    // Default constructor
    property() = default;

    // Copy constructor
    property(const property& other)
    {
        m_meta.m_getter = other.m_meta.m_getter;
        m_meta.m_setter = other.m_meta.m_setter;
        m_meta.m_deleter = other.m_meta.m_deleter;
        m_meta.m_value = other.m_meta.m_value;
    }

    // Move constructor
    property(property&& other) noexcept
    {
        m_meta.m_getter = std::move(other.m_meta.m_getter);
        m_meta.m_setter = std::move(other.m_meta.m_setter);
        m_meta.m_deleter = std::move(other.m_meta.m_deleter);
        m_meta.m_value = std::move(other.m_meta.m_value);
    }

    // Copy value constructor
    explicit property(const value_t& other)
    {m_meta.m_value = other;}

    // Move value constructor
    explicit property(value_t&& other)
    {m_meta.m_value = std::move(other);}

    // Destructor calls the deleter
    ~property()
    {m_meta.m_deleter();}

    // Delete assignment operators (prevent accidental copying instead of setting value with operator()() from another
    // property)
    auto operator=(const property&) -> property& = delete;
    auto operator=(property&&) noexcept -> property& = delete;

    // Getter and setter operators for the property
    auto operator()() const -> decltype(auto) {return m_meta.m_getter();}
    auto operator=(const value_t& value) -> value_t {return m_meta.m_setter(value);}
    auto operator=(value_t&& value) -> value_t {return m_meta.m_setter(std::move(value));}

    // Dereferencing accesses the inner value type of the property (for custom getters and setters)
    auto operator*() -> auto& {assert(!m_locked); return m_meta.m_value;}
    auto operator*() const -> const auto& {assert(!m_locked); return m_meta.m_value;}

private:
    detail::meta_property<value_t> m_meta;
};


/**
 * The access_meta class contains a group of static methods that are all friends to the property and meta_property
 * class, and can therefore mutate the contents of them - this includes settings custom getter/setter/deleter method,
 * as well as locking and unlocking internal values of the property
 */
struct access_meta
{
    // Bind a new getter method to the property
    template <typename T>
    static auto bind_getter(ext::property<T>& property, typename decltype(property.m_meta)::getter_t&& getter) -> void
    {property.m_meta.m_getter = std::move(getter);};

    // Bind a new setter method to the property
    template <typename T>
    static auto bind_setter(ext::property<T>& property, typename decltype(property.m_meta)::setter_t&& setter) -> void
    {property.m_meta.m_setter = std::move(setter);};

    // Bind a new deleter method to the property
    template <typename T>
    static auto bind_deleter(ext::property<T>& property, typename decltype(property.m_meta)::deleter_t&& deleter) -> void
    {property.m_meta.m_deleter = std::move(deleter);};

    // Unlock access to a property's internal value
    template <typename T>
    static auto unlock(ext::property<T>& property)
    {property.unlock();}

    // Lock access to a property's internal value
    template <typename T>
    static auto lock(ext::property<T>& property)
    {property.lock();}
};


/**
 * The property guard gives a method temporary access to the internal value stored by a property - this is used when
 * custom getters and setters need to access the internal value pre-/post-mutation
 * @tparam T Underlying type of the property
 */
template <typename T>
struct property_guard
{
public:
    // The constructor of the property guard unlocks the property, allowing code after its declaration to access the
    // internal value of the property
    explicit property_guard(ext::property<T>& property): m_property(property)
    {access_meta::unlock(m_property);};

    // The destructor of the property guard re-locks the property, so that code in other sections (after the accessor is
    // called) can not access the internal value of the property (destructor called after accessor returns)
    ~property_guard()
    {access_meta::lock(m_property);}

private:
    // Reference to the property being unlocked and re-locked
    ext::property<T>& m_property;
};

// Wrapper around access_meta::bind_getter, with a lambda wrapper
#define bind_get(property) access_meta::bind_getter(property, [this] {return get_##property();})

// Wrapper around access_meta::bind_setter, with a lambda wrapper and perfect forwarding
#define bind_set(property) access_meta::bind_setter(property, [this]<typename T>(T&& val) mutable {set_##property(std::forward<T>(val)); return std::forward<T>(val);})

// Wrapper around access_meta::bind_deleter, with a lambda wrapper
#define bind_del(property) access_meta::bind_deleter(property, [this] {del_##property();})

// Wrapper around property_guard, with a const_cast<T>, so that it works in const getter methods too
#define guard_property(property) property_guard guard##_property{const_cast<std::remove_const_t<decltype(property)>&>(property)}


#define SET_PROPERTY_FROM_OPTIONS(options, property, default_) property(options.try_emplace(_EXT snake_to_camel(#property), default_).first->second.template to<decltype(property)::value_t>())
#define SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(options, property) property(options.try_emplace(_EXT snake_to_camel(#property)).first->second.template to<decltype(property)::value_t>())



#endif //SBROWSER2_PROPERTY_HPP
