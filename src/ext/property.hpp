#pragma once
#ifndef SBROWSER2_PROPERTY_HPP
#define SBROWSER2_PROPERTY_HPP

namespace ext {template <typename _Tx, bool ce_reactions> class property;}

#include <iostream>
#include <memory>
#include <utility>

#include <ext/keywords.hpp>
#include <ext/type_traits.hpp>
#include <ext/detail/meta_property.hpp>

template <typename _Tx, bool ce_reactions>
class ext::property
{
public constructors:
    property() = default;
    ~property() {_Meta._Deleter();};

    property(const property&) = delete;
    property(property&&) noexcept = delete;
    auto operator=(const property&) -> property& = delete;
    auto operator=(property&&) noexcept -> property& = delete;

    property(const _Tx& _Other) : _Meta(_Other) {}
    property(_Tx&& _Other) noexcept : _Meta(std::forward<_Tx>(_Other)) {}

public cpp_operators:
    // member access
    auto operator*() -> _Tx& {verify_lock return _Meta.M_Val;}
    auto operator->() const {return &_Meta._Getter();}
    auto operator->() const -> auto requires is_smart_pointer_v<_Tx> {return _Meta._Getter().get();}
    auto operator->() const -> auto requires std::is_pointer_v<_Tx> {return _Meta._Getter();}

    // getter
    operator _Tx() const requires (not is_smart_pointer_v<_Tx>) {return _Meta.getter();}
    template <typename U> operator U() const requires (is_smart_pointer_v<_Tx>) {return _Meta.getter().get();}

    // setter
    auto operator=(_Tx&& _That) noexcept;
    auto operator=(const _Tx& that) -> property& {operator=(std::move(that));}

    // comparison operators
    template <typename U> auto operator==(const U& that) -> bool {return _Meta.m_value == that;}
    template <typename U> auto operator!=(const U& that) -> bool {return _Meta.m_value != that;}
    template <typename U> auto operator> (const U& that) -> bool {return _Meta.m_value >  that;}
    template <typename U> auto operator< (const U& that) -> bool {return _Meta.m_value <  that;}
    template <typename U> auto operator>=(const U& that) -> bool {return _Meta.m_value >= that;}
    template <typename U> auto operator<=(const U& that) -> bool {return _Meta.m_value <= that;}

    // assignment operators
    template <typename U> auto operator+=(const U& that) -> property& {_Meta.m_value += that; return *this;}
    template <typename U> auto operator-=(const U& that) -> property& {_Meta.m_value -= that; return *this;}
    template <typename U> auto operator*=(const U& that) -> property& {_Meta.m_value *= that; return *this;}
    template <typename U> auto operator/=(const U& that) -> property& {_Meta.m_value /= that; return *this;}
    template <typename U> auto operator%=(const U& that) -> property& {_Meta.m_value %= that; return *this;}

    // arithmetic operators
    template <typename U> auto operator+(const U& that) const -> property {return property{_Meta.m_value += that};}
    template <typename U> auto operator-(const U& that) const -> property {return property{_Meta.m_value -= that};}
    template <typename U> auto operator*(const U& that) const -> property {return property{_Meta.m_value *= that};}
    template <typename U> auto operator/(const U& that) const -> property {return property{_Meta.m_value /= that};}
    template <typename U> auto operator%(const U& that) const -> property {return property{_Meta.m_value %= that};}

    // increment operators
    template <typename U> auto operator++() -> property& {++_Meta.m_value; return *this;}
    template <typename U> auto operator--() -> property& {--_Meta.m_value; return *this;}
    template <typename U> auto operator++(const int) const -> property {return property{_Meta.m_value++};}
    template <typename U> auto operator--(const int) const -> property {return property{_Meta.m_value--};}

    // boolean operator
    operator bool() const {return static_cast<bool>(_Meta.getter());}

public cpp_properties:
    detail::meta_property<_Tx, ce_reactions> _Meta;
};


template <typename _Ty2, typename _Ty1>
inline auto p_static_cast(const ext::property<_Ty1>& _That) -> ext::property<_Ty2>
{
    // apply a dynamic_cast to a property's value
    unlock_property(_That)
    return property<_Ty2>(dynamic_cast<_Ty2>(*_That));
    lock_property(_That)
}


template <typename _Ty2, typename _Ty1>
inline auto p_dynamic_cast(const ext::property<_Ty1>& _That) -> ext::property<_Ty2>
{
    // apply a static_cast to a property's value
    unlock_property(_That)
    return property<_Ty2>(static_cast<_Ty2>(*_That));
    lock_property(_That)
}


template <typename _Ty2, typename _Ty1>
inline auto p_const_cast(const ext::property<_Ty1>& _That) -> ext::property<_Ty2>
{
    // apply a const_cast to a property's value
    unlock_property(_That)
    return property<_Ty2>(const_cast<_Ty2>(*_That));
    lock_property(_That)
}


template <typename _Ty2, typename _Ty1>
inline auto p_reinterpret_cast(const ext::property<_Ty1>& _That) -> ext::property<_Ty2>
{
    // apply a reinterpret_cast to a property's value
    unlock_property(_That)
    return property<_Ty2>(reinterpret_cast<_Ty2>(*_That));
    lock_property(_That)
}


template <typename _Ty2, typename _Ty1>
inline auto p_any_cast(const ext::property<_Ty1>& _That) -> ext::property<_Ty2>
{
    // apply an any_cast to a property's value
    unlock_property(_That)
    return property<_Ty2>((*_That).template to<_Ty2>());
    lock_property(_That)
}


template <typename _Ty2, typename _Ty1>
inline auto p_bit_cast(const ext::property<_Ty1>& _That) -> ext::property<_Ty2>
{
    // apply a bit_cast to a property's value
    unlock_property(_That)
    return property<_Ty2>(std::bit_cast<_Ty2>(*_That));
    lock_property(_That)
}


#endif //SBROWSER2_PROPERTY_HPP
