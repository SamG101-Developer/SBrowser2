#pragma once
#include "ext/concepts.hpp"
#ifndef SBROWSER2_PROPERTY_HPP
#define SBROWSER2_PROPERTY_HPP

#include <memory>
#include "ext/streams.hpp"
#include "ext/detail/meta_property.hpp"
namespace ext {template <typename ...Ts> class property;}

#define FORWARD_INNER_VALUE_OPERATOR(op)      \
    template <typename V>                     \
    auto operator op (V&& val)                \
    {m_meta.m_value op std::forward<V>(val);} \
// TODO : <, > etc

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

    // Copy constructor
    property(const property& other)
            : m_meta(detail::meta_property<value_t>{
                .m_getter = other.m_meta.m_getter,
                .m_setter = other.m_meta.m_setter,
                .m_deleter = other.m_meta.m_deleter,
                .m_value = other.m_meta.m_value
            })
    {}

    // Move constructor
    property(property&& other) noexcept
            : m_meta(detail::meta_property<value_t>{
                .m_getter = std::move(other.m_meta.m_getter),
                .m_setter = std::move(other.m_meta.m_setter),
                .m_deleter = std::move(other.m_meta.m_deleter),
                .m_value = std::move(other.m_meta.m_value)
            })
    {}

    // Copy value constructor
    explicit property(const value_t& other)
    {m_meta.m_value.reset(other);}

    // Move value constructor
    explicit property(value_t&& other)
    {m_meta.m_value.reset(std::move(other));}

    // Special nullptr_t constructor
    explicit property(std::nullptr_t&&)
    {m_meta.m_value = nullptr;}

    // Special move std::unique_ptr<T> constructor
    explicit property(std::unique_ptr<T>&& other)
    {m_meta.m_value = std::move(other);}

    // Destructor calls the deleter
    ~property()
    {m_meta.m_deleter();}


    auto operator=(const property&) -> property& = default;
    auto operator=(property&&) noexcept -> property& = default;

    // Getter and setter operators for the property (because T is a std::unique_ptr<T>, a raw pointer is used as the
    // type of variable for the setter's parameter and the getters return type
    auto operator()() const -> decltype(auto) {return m_meta.m_getter();}
    auto operator=(const value_t& value) -> decltype(auto) {return m_meta.m_setter(value);}
    auto operator=(value_t&& value) -> decltype(auto) {return m_meta.m_setter(std::move(value));}
    auto operator=(std::unique_ptr<T>&& value) -> decltype(auto) {return m_meta.m_setter(std::move(value).get());} // TODO

    // Dereferencing accesses the inner value type of the property (for custom getters and setters), so move the
    // std::unique_ptr out of the meta property to the return value. Check the property is unlocked before accessing the
    // internal value
    auto operator*() -> decltype(auto) {assert(!m_locked); return std::move(m_meta.m_value);}
    auto operator*() const -> decltype(auto) {assert(!m_locked); return std::move(m_meta.m_value);}

private:
    detail::meta_property<std::unique_ptr<T>> m_meta;
};


/**
 * Property class for basic type T (non-specialized). It contain teh copy and move semantics, the setting and getting of
 * the value inside the property, and the dereferencing
 * @tparam T Underlying type of the property
 */
template <typename T>
class ext::property<T> : private detail::lockable
{
public:
    // Access to the value type
    friend struct ::access_meta;
    using value_t = T;

    // Default constructor
    property() = default;

    // Copy constructor
    property(const property& other)
            : m_meta(detail::meta_property<value_t>{
                .m_getter = other.m_meta.m_getter,
                .m_setter = other.m_meta.m_setter,
                .m_deleter = other.m_meta.m_deleter,
                .m_value = other.m_meta.m_value
            })
    {}

    // Move constructor
    property(property&& other) noexcept
            : m_meta(detail::meta_property<value_t>{
                .m_getter = std::move(other.m_meta.m_getter),
                .m_setter = std::move(other.m_meta.m_setter),
                .m_deleter = std::move(other.m_meta.m_deleter),
                .m_value = std::move(other.m_meta.m_value)
            })
    {}

    // Copy value constructor
    explicit property(const value_t& other)
    {m_meta.m_value = other;}

    // Move value constructor
    explicit property(value_t&& other)
    {m_meta.m_value = std::move(other);}

    // Destructor calls the deleter
    ~property()
    {m_meta.m_deleter();}


    auto operator=(const property& other) -> property&
    {
        m_meta.m_getter = other.m_meta.m_getter;
        m_meta.m_setter = other.m_meta.m_setter;
        m_meta.m_deleter = other.m_meta.m_deleter;
        m_meta.m_value = other.m_meta.m_value;
        return *this;
    };

    auto operator=(property&& other) noexcept -> property&
    {
        m_meta.m_getter = std::move(other.m_meta.m_getter);
        m_meta.m_setter = std::move(other.m_meta.m_setter);
        m_meta.m_deleter = std::move(other.m_meta.m_deleter);
        m_meta.m_value = std::move(other.m_meta.m_value);
        return *this;
    };

    // Getter and setter operators for the property
    auto operator()() const -> decltype(auto) {return m_meta.m_getter();}
    auto operator=(const value_t& value) -> decltype(auto) {return m_meta.m_setter(value);}
    auto operator=(value_t&& value) -> decltype(auto) {return m_meta.m_setter(std::move(value));}

    // Dereferencing accesses the inner value type of the property (for custom getters and setters)
    auto operator*() -> decltype(auto) {assert(!m_locked); return m_meta.m_value;}
    auto operator*() const -> decltype(auto) {assert(!m_locked); return m_meta.m_value;}

    FORWARD_INNER_VALUE_OPERATOR(+=)
    FORWARD_INNER_VALUE_OPERATOR(-=)
    FORWARD_INNER_VALUE_OPERATOR(*=)
    FORWARD_INNER_VALUE_OPERATOR(/=)
    FORWARD_INNER_VALUE_OPERATOR(%=)

private:
    detail::meta_property<value_t> m_meta;
};


template <template <typename> typename T, typename U> requires (!type_is<T<U>, std::unique_ptr<U>>)
class ext::property<T<U>> : private detail::lockable
{
public:
    // Access to the value type
    friend struct ::access_meta;
    using value_t = T<U>;
    template <typename V> using stripped_value_t = T<V>;

    // Default constructor
    property() = default;

    // Copy constructor
    property(const property<value_t>& other)
            : m_meta(detail::meta_property<value_t>{
                .m_getter = other.m_meta.m_getter,
                .m_setter = other.m_meta.m_setter,
                .m_deleter = other.m_meta.m_deleter,
                .m_value = other.m_meta.m_value
            })
    {}

    template <typename V>
    property(const property<stripped_value_t<V>>& other)
            : m_meta(detail::meta_property<value_t>{
                .m_getter = other.m_meta.m_getter,
                .m_setter = other.m_meta.m_setter,
                .m_deleter = other.m_meta.m_deleter,
                .m_value = other.m_meta.m_value
            })
    {}

    // Move constructor
    property(property<value_t>&& other)
            : m_meta(detail::meta_property<value_t>{
                .m_getter = std::move(other.m_meta.m_getter),
                .m_setter = std::move(other.m_meta.m_setter),
                .m_deleter = std::move(other.m_meta.m_deleter),
                .m_value = std::move(other.m_meta.m_value)
            })
    {}

    template <typename V>
    property(property<stripped_value_t<V>>&& other)
            : m_meta(detail::meta_property<value_t>{
                .m_getter = std::move(other.m_meta.m_getter),
                .m_setter = std::move(other.m_meta.m_setter),
                .m_deleter = std::move(other.m_meta.m_deleter),
                .m_value = std::move(other.m_meta.m_value)
            })
    {}

    // Copy value constructor
    template <typename V>
    explicit property(const stripped_value_t<V>& other)
    {m_meta.m_value = other;}

    // Move value constructor
    template <typename V>
    explicit property(stripped_value_t<V>&& other)
    {m_meta.m_value = std::move(other);}

    // Special constructor from templated inner type TODO : concept restraint?
    template <typename V>
    explicit property(V value)
    {m_meta.m_value = value;}

    // Destructor calls deleter
    ~property()
    {m_meta.m_deleter();}


    auto operator=(const property& other) -> property&
    {
        m_meta.m_getter = other.m_meta.m_getter;
        m_meta.m_setter = other.m_meta.m_setter;
        m_meta.m_deleter = other.m_meta.m_deleter;
        m_meta.m_value = other.m_meta.m_value;
        return *this;
    };

    auto operator=(property&& other) noexcept -> property&
    {
        m_meta.m_getter = std::move(other.m_meta.m_getter);
        m_meta.m_setter = std::move(other.m_meta.m_setter);
        m_meta.m_deleter = std::move(other.m_meta.m_deleter);
        m_meta.m_value = std::move(other.m_meta.m_value);
        return *this;
    };

    // Getter and setter operators for the property
    auto operator()() const -> decltype(auto) {return m_meta.m_getter();}
    template <typename V> auto operator=(const stripped_value_t<V>& value) -> decltype(auto) {return m_meta.m_setter((stripped_value_t<U>)value);}
    template <typename V> auto operator=(stripped_value_t<V>&& value) -> decltype(auto) {return m_meta.m_setter((stripped_value_t<U>)std::move(value));}

    // Dereferencing accesses the inner value type of the property (for custom getters and setters)
    auto operator*() -> decltype(auto) {assert(!m_locked); return m_meta.m_value;}
    auto operator*() const -> decltype(auto) {assert(!m_locked); return m_meta.m_value;}

    FORWARD_INNER_VALUE_OPERATOR(+=)
    FORWARD_INNER_VALUE_OPERATOR(-=)
    FORWARD_INNER_VALUE_OPERATOR(*=)
    FORWARD_INNER_VALUE_OPERATOR(/=)
    FORWARD_INNER_VALUE_OPERATOR(%=)

private:
    detail::meta_property<stripped_value_t<U>> m_meta;
};


template <typename ...Ts> requires (sizeof...(Ts) > 1)
class ext::property<Ts...> : private detail::lockable
{
    // Access to the value type
    friend struct ::access_meta;
    using value_t = ext::variant<Ts...>;

    // Default constructor
    property() = default;

    // Copy constructor
    template <typename ...Ts1>
    property(const property<Ts1...>& other)
    {
        m_meta.m_getter = other.m_meta.m_getter;
        m_meta.m_setter = other.m_meta.m_setter;
        m_meta.m_deleter = other.m_meta.m_deleter;
        m_meta.m_value = other.m_meta.m_value;
    }

    template <typename ...Ts1>
    property(property<Ts1...>&& other)
    {
        m_meta.m_getter = std::move(other.m_meta.m_getter);
        m_meta.m_setter = std::move(other.m_meta.m_setter);
        m_meta.m_deleter = std::move(other.m_meta.m_deleter);
        m_meta.m_value = std::move(other.m_meta.m_value);
    }

    // Copy value constructor
    template <typename T>
    explicit property(const T& other)
    {m_meta.m_value = other;}

    // Move value constructor
    template <typename T>
    explicit property(T&& other)
    {m_meta.m_value = std::move(other);}

    // Special constructor for variant
    explicit property(value_t other)
    {m_meta.m_value = other;}

    // Destructor calls the deleter
    ~property()
    {m_meta.m_deleter();}

    auto operator=(const property& other) -> property&
    {
        m_meta.m_getter = other.m_meta.m_getter;
        m_meta.m_setter = other.m_meta.m_setter;
        m_meta.m_deleter = other.m_meta.m_deleter;
        m_meta.m_value = other.m_meta.m_value;
        return *this;
    };

    auto operator=(property&& other) noexcept -> property&
    {
        m_meta.m_getter = std::move(other.m_meta.m_getter);
        m_meta.m_setter = std::move(other.m_meta.m_setter);
        m_meta.m_deleter = std::move(other.m_meta.m_deleter);
        m_meta.m_value = std::move(other.m_meta.m_value);
        return *this;
    };

    // Getter and setter operators for the property
    auto operator()() const -> decltype(auto) {return m_meta.m_getter();}
    template <typename T> auto operator=(const T& value) -> decltype(auto) {return m_meta.m_setter(value);}
    template <typename T> auto operator=(T&& value) -> decltype(auto) {return m_meta.m_setter(std::move(value));}
    auto operator=(value_t value) -> decltype(auto) {return m_meta.m_setter(value);}

    // Dereferencing accesses the inner value type of the property (for custom getters and setters)
    auto operator*() -> decltype(auto) {assert(!m_locked); return m_meta.m_value;}
    auto operator*() const -> decltype(auto) {assert(!m_locked); return m_meta.m_value;}

    FORWARD_INNER_VALUE_OPERATOR(+=)
    FORWARD_INNER_VALUE_OPERATOR(-=)
    FORWARD_INNER_VALUE_OPERATOR(*=)
    FORWARD_INNER_VALUE_OPERATOR(/=)
    FORWARD_INNER_VALUE_OPERATOR(%=)

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
 * custom getters and setters need to access the internal value [pre/post]-mutation
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
#define bind_get(property) access_meta::bind_getter(this->property, [this] {return get_##property();})

// Wrapper around access_meta::bind_setter, with a lambda wrapper and perfect forwarding
#define bind_set(property) access_meta::bind_setter(this->property, [this]<typename T>(T&& val) mutable {set_##property(std::forward<T>(val)); return std::forward<T>(val);})

// Wrapper around access_meta::bind_deleter, with a lambda wrapper
#define bind_del(property) access_meta::bind_deleter(this->property, [this] {del_##property();})

// Wrapper around property_guard, with a const_cast<T>, so that it works in const getter methods too
#define guard_property(property) property_guard guard##_property{const_cast<std::remove_const_t<decltype(this->property)>&>(this->property)}


#define SET_PROPERTY_FROM_OPTIONS(options, property, default_) property{options.try_emplace(_EXT snake_to_camel(#property), default_).first->second.template to<decltype(property)::value_t>()}
#define SET_PROPERTY_FROM_OPTIONS_NO_DEFAULT(options, property) property{options.try_emplace(_EXT snake_to_camel(#property)).first->second.template to<decltype(property)::value_t>()}
#define DEFINE_CUSTOM_SETTER(p) auto set_##p(const typename decltype(p)::value_t& val) -> void
#define DEFINE_CUSTOM_GETTER(p) auto get_##p() const -> typename decltype(this->p)::value_t
#define DEFINE_CUSTOM_DELETER(p) auto del_##p() -> void
#define PUT_FORWARDS(p) auto operator=(const typename decltype(p)::value_t& val) -> decltype(auto) {p = val; return *this;}

#define DEFINE_GETTER(p, t) _EXT_NODISCARD auto get_##p() const -> t
#define DEFINE_SETTER(p, t) auto set_##p(t new_ ## p) -> t


_EXT_BEGIN

template <typename T, typename U, typename V>
class attribute_watcher
{
public constructors:
    attribute_watcher(T&& object, U&& attribute)
            : m_object{std::forward<T>(object)}
            , m_attribute{std::forward<U>(attribute)}
            , m_start_value{current_value()}
    {};

public cpp_members:
    auto has_changed() -> ext::boolean {return m_start_value != current_value();};
    auto current_value() -> V {return std::mem_fn(m_attribute)(m_object);}

private:
    T m_object;
    U m_attribute;
    V m_start_value;
};


template <typename T, typename U>
attribute_watcher(T&& object, U&& attribute) -> attribute_watcher<T, U, decltype(std::mem_fn(std::forward<U>(attribute))(std::forward<T>(object)))>;

_EXT_END


#endif //SBROWSER2_PROPERTY_HPP
