#pragma once
#ifndef SBROWSER2_PROPERTY_HPP
#define SBROWSER2_PROPERTY_HPP

namespace ext {template <typename _Tx, bool ce_reactions> class property;}

#include <iostream>
#include <memory>
#include <utility>

#include "ext/keywords.hpp"
#include "ext/type_traits.hpp"
#include "ext/detail/guard_property.hpp"

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
    explicit property(const property& _Other) = default;

    explicit property(property&& _Other) noexcept = delete;

    [[deprecated("Check if this CTor should be used, or if operator=(_Tx) should be used")]]
    auto operator=(const property& _Other) -> property& = default;

    auto operator=(property&& _Other) noexcept -> property& = delete;

    // assign a starting value for the property
    property(const outer_val_t& _OtherToCopy) requires is_dumb_property : _Meta(_OtherToCopy) {} // set new object (const ref)
    property(outer_val_t&& _OtherToMove) noexcept requires is_dumb_property : _Meta(std::forward<outer_val_t>(_OtherToMove)) {} // set new object (movable)

    property(outer_val_t&& _OtherSmartPointerToMove) noexcept requires is_smart_property {_Meta._Val = std::move(_OtherSmartPointerToMove);} // set unique_ptr to a new unique pointer
    property(inner_val_t   _OtherRawPointerToLink) requires is_smart_property {_Meta._Val.reset(_OtherRawPointerToLink);}

public cpp_operators:
    // member access
    auto operator* ()       -> auto&;
    auto operator* () const -> const auto&;

    // getter
    auto operator()() const -> inner_val_t {return _Meta._Getter();}

    // setter
    auto operator=(const outer_val_t& _OtherToCopy)
            -> inner_val_t {return _Meta._Setter(_OtherToCopy);}

    auto operator=(outer_val_t&& _OtherToMove) noexcept
            -> inner_val_t {return _Meta._Setter(std::forward<outer_val_t>(_OtherToMove));}

    auto operator=(dynamically_castable_to<inner_val_t> auto _OtherPtr)
            -> inner_val_t requires (is_smart_property) {return _Meta._Setter((inner_val_t)_OtherPtr);}

    auto operator=(std::nullptr_t)
            -> inner_val_t requires (is_smart_property) {return _Meta._Setter(nullptr);}

    // auto operator=(inner_val_t _OtherRawPointerToLink) -> void requires is_smart_property {_Meta._Setter(_OtherRawPointerToLink);}

    auto operator+(auto&& _Other) const -> auto {return _Meta._Val + std::forward<_Tx>(_Other);}
    auto operator-(auto&& _Other) const -> auto {return _Meta._Val - std::forward<_Tx>(_Other);}
    auto operator*(auto&& _Other) const -> auto {return _Meta._Val * std::forward<_Tx>(_Other);}
    auto operator/(auto&& _Other) const -> auto {return _Meta._Val / std::forward<_Tx>(_Other);}
    auto operator%(auto&& _Other) const -> auto {return _Meta._Val % std::forward<_Tx>(_Other);}

    auto operator+=(auto&& _Other) -> property& {_Meta._Val += std::forward<_Tx>(_Other); return *this;}
    auto operator-=(auto&& _Other) -> property& {_Meta._Val -= std::forward<_Tx>(_Other); return *this;}
    auto operator*=(auto&& _Other) -> property& {_Meta._Val *= std::forward<_Tx>(_Other); return *this;}
    auto operator/=(auto&& _Other) -> property& {_Meta._Val /= std::forward<_Tx>(_Other); return *this;}
    auto operator%=(auto&& _Other) -> property& {_Meta._Val %= std::forward<_Tx>(_Other); return *this;}

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


template <typename _Ty2, typename _Ty1>
inline auto p_static_cast(ext::property<_Ty1>& _That) -> _Ty2
{
    // apply a dynamic_cast to a property's value
    property_guard(_That);
    return dynamic_cast<_Ty2>(*_That);
}


template <typename _Ty2, typename _Ty1>
inline auto p_dynamic_cast(ext::property<_Ty1>& _That) -> _Ty2
{
    // apply a static_cast to a property's value
    property_guard(_That);
    return static_cast<_Ty2>(*_That);
}


template <typename _Ty2, typename _Ty1>
inline auto p_const_cast(ext::property<_Ty1>& _That) -> _Ty2
{
    // apply a const_cast to a property's value
    property_guard(_That);
    return const_cast<_Ty2>(*_That);
}


template <typename _Ty2, typename _Ty1>
inline auto p_reinterpret_cast(ext::property<_Ty1>& _That) -> _Ty2
{
    // apply a reinterpret_cast to a property's value
    property_guard(_That);
    return reinterpret_cast<_Ty2>(*_That);
}


template <typename _Ty2, typename _Ty1>
inline auto p_any_cast(ext::property<_Ty1>& _That) -> _Ty2
{
    // apply an any_cast to a property's value
    property_guard(_That);
    return (*_That).template to<_Ty2>();
}


template <typename _Ty2, typename _Ty1>
inline auto p_bit_cast(ext::property<_Ty1>& _That) -> _Ty2
{
    // apply a bit_cast to a property's value
    property_guard(_That);
    return std::bit_cast<_Ty2>(*_That);
}


#endif //SBROWSER2_PROPERTY_HPP
