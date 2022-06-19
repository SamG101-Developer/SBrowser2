#pragma once
#ifndef SBROWSER2_PROPERTY_HPP
#define SBROWSER2_PROPERTY_HPP

namespace ext {template <typename _Tx, bool ce_reactions> class property;}

#include <iostream>
#include <memory>
#include <utility>

#include <ext/keywords.hpp>
#include <ext/type_traits.hpp>
#include <ext/detail/guard_property.hpp>

template <typename _Tx, bool ce_reactions>
class ext::property
{
public aliases:
    using outer_val_t = _Tx;                                 // unique_ptr<node>, node*, etc
    using inner_val_t = unwrap_smart_pointer_t<outer_val_t>; // node*           , node*, etc

public constructors:
    property() = default;
    ~property() {_Meta._Deleter();};

    [[deprecated("Check if this CTor should be used, or if operator()() should be used")]]
    property(const property& _Other) = default;
    [[deprecated("Check if this CTor should be used, or if operator()() should be used")]]
    property(property&& _Other) noexcept = default;
    [[deprecated("Check if this CTor should be used, or if operator=(T) should be used")]]
    auto operator=(const property& _Other) -> property& = default;
    [[deprecated("Check if this CTor should be used, or if operator=(T) should be used")]]
    auto operator=(property&& _Other) noexcept -> property& = default;

    // assign a starting value for the property
    property(const outer_val_t& _OtherToCopy) requires is_dumb_property : _Meta(_OtherToCopy) {} // set new object (const ref)
    property(outer_val_t&& _OtherToMove) noexcept requires is_dumb_property : _Meta(std::forward<outer_val_t>(_OtherToMove)) {} // set new object (movable)

    property(outer_val_t&& _OtherSmartPointerToMove) noexcept requires is_smart_property {_Meta._Val = std::move(_OtherSmartPointerToMove);} // set unique_ptr to a new unique pointer
    property(inner_val_t   _OtherRawPointerToLink) noexcept requires is_smart_property {_Meta._Val.reset(_OtherRawPointerToLink);}

public cpp_operators:
    // member access
    auto operator* ()       -> auto&;
    auto operator* () const -> const auto&;
    auto operator->()       -> auto&;
    auto operator->() const -> const auto&;

    // javascript getter
    auto operator()() const -> auto {return _Meta._Getter();}

    // javascript setter
    auto operator=(const outer_val_t& _OtherToCopy) -> void {_Meta._Setter(_OtherToCopy);}
    auto operator=(outer_val_t&& _OtherToMove) noexcept -> void {_Meta._Setter(std::forward<_Tx>(_OtherToMove));}

    template <typename derived_from_inner_val_t>
    auto operator=(derived_from_inner_val_t _OtherRawPointerToLink)
            -> void requires (is_smart_property && is_dynamically_castable_to_v<inner_val_t, derived_from_inner_val_t>) {_Meta._Setter((inner_val_t)_OtherRawPointerToLink);}

//    auto operator=(inner_val_t _OtherRawPointerToLink) -> void requires is_smart_property {_Meta._Setter(_OtherRawPointerToLink);}

    // comparison operators
    auto operator==(const ext::property<_Tx>& _That) const -> bool {return _Meta._Getter() == _That;}
    auto operator!=(const ext::property<_Tx>& _That) const -> bool {return _Meta._Getter() != _That;}
    auto operator> (const ext::property<_Tx>& _That) const -> bool {return _Meta._Getter() >  _That;}
    auto operator< (const ext::property<_Tx>& _That) const -> bool {return _Meta._Getter() <  _That;}
    auto operator>=(const ext::property<_Tx>& _That) const -> bool {return _Meta._Getter() >= _That;}
    auto operator<=(const ext::property<_Tx>& _That) const -> bool {return _Meta._Getter() <= _That;}

    // assignment operators
    auto operator+=(const ext::property<_Tx>& _That) -> property& {_Meta._Getter() += _That; return *this;}
    auto operator-=(const ext::property<_Tx>& _That) -> property& {_Meta._Getter() -= _That; return *this;}
    auto operator*=(const ext::property<_Tx>& _That) -> property& {_Meta._Getter() *= _That; return *this;}
    auto operator/=(const ext::property<_Tx>& _That) -> property& {_Meta._Getter() /= _That; return *this;}
    auto operator%=(const ext::property<_Tx>& _That) -> property& {_Meta._Getter() %= _That; return *this;}

    // arithmetic operators
    auto operator+(const ext::property<_Tx>& _That) const -> property {return property{_Meta._Getter() += _That};}
    auto operator-(const ext::property<_Tx>& _That) const -> property {return property{_Meta._Getter() -= _That};}
    auto operator*(const ext::property<_Tx>& _That) const -> property {return property{_Meta._Getter() *= _That};}
    auto operator/(const ext::property<_Tx>& _That) const -> property {return property{_Meta._Getter() /= _That};}
    auto operator%(const ext::property<_Tx>& _That) const -> property {return property{_Meta._Getter() %= _That};}

    // increment operators
    auto operator++() -> property& {++_Meta._Val; return *this;}
    auto operator--() -> property& {--_Meta._Val; return *this;}
    auto operator++(const int) const -> property {return property{_Meta._Val++};}
    auto operator--(const int) const -> property {return property{_Meta._Val--};}

    // boolean operator
    operator bool() const {return static_cast<bool>(_Meta._Getter());}

public cpp_properties:
    detail::meta_property<_Tx, ce_reactions> _Meta;
};


template <typename _Ty, bool ce_reactions>
auto ext::property<_Ty, ce_reactions>::operator*() -> auto&
{
    // get the internal value (internal pointer of smart pointer, or object)
    verify_lock
    return _Meta._Val;
}


template <typename _Ty, bool ce_reactions>
auto ext::property<_Ty, ce_reactions>::operator*() const -> const auto&
{
    // get the internal value (internal pointer of smart pointer, or object)
    verify_lock
    return _Meta._Val;
}


template <typename _Ty, bool ce_reactions>
auto ext::property<_Ty, ce_reactions>::operator->() -> auto&
{
    // get the internal value (object of (smart)pointer, or address)
    if constexpr(std::is_pointer_v<_Ty> || is_smart_pointer_v<_Ty>)
        return _Meta._Val;
    else
        return &_Meta._Val;
}


template <typename _Ty, bool ce_reactions>
auto ext::property<_Ty, ce_reactions>::operator->() const -> const auto&
{
    // get the internal value (object of (smart)pointer, or address)
    if constexpr(std::is_pointer_v<_Ty> || is_smart_pointer_v<_Ty>)
        return _Meta._Val;
    else
        return &_Meta._Val;
}


template <typename _Ty2, typename _Ty1>
inline auto p_static_cast(ext::property<_Ty1>& _That) -> ext::property<_Ty2>
{
    // apply a dynamic_cast to a property's value
    property_guard(_That);
    return ext::property<_Ty2>(dynamic_cast<_Ty2>(*_That));
}


template <typename _Ty2, typename _Ty1>
inline auto p_dynamic_cast(ext::property<_Ty1>& _That) -> ext::property<_Ty2>
{
    // apply a static_cast to a property's value
    property_guard(_That);
    return ext::property<_Ty2>(static_cast<_Ty2>(*_That));
}


template <typename _Ty2, typename _Ty1>
inline auto p_const_cast(ext::property<_Ty1>& _That) -> ext::property<_Ty2>
{
    // apply a const_cast to a property's value
    property_guard(_That);
    return ext::property<_Ty2>(const_cast<_Ty2>(*_That));
}


template <typename _Ty2, typename _Ty1>
inline auto p_reinterpret_cast(ext::property<_Ty1>& _That) -> ext::property<_Ty2>
{
    // apply a reinterpret_cast to a property's value
    property_guard(_That);
    return ext::property<_Ty2>(reinterpret_cast<_Ty2>(*_That));
}


template <typename _Ty2, typename _Ty1>
inline auto p_any_cast(ext::property<_Ty1>& _That) -> ext::property<_Ty2>
{
    // apply an any_cast to a property's value
    property_guard(_That);
    return ext::property<_Ty2>((*_That).template to<_Ty2>());
}


template <typename _Ty2, typename _Ty1>
inline auto p_bit_cast(ext::property<_Ty1>& _That) -> ext::property<_Ty2>
{
    // apply a bit_cast to a property's value
    property_guard(_That);
    return ext::property<_Ty2>(std::bit_cast<_Ty2>(*_That));
}


#endif //SBROWSER2_PROPERTY_HPP
