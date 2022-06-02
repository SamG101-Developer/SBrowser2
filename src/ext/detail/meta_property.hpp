#pragma once
#ifndef SBROWSER2_META_PROPERTY_HPP
#define SBROWSER2_META_PROPERTY_HPP

#define bind_get(p, method) p._Meta._Getter  = [this] -> typename decltype(p)::value_type {return method();};
#define bind_set(p, method) p._Meta._Setter  = [this](auto&& _Val) {method(std::forward<decltype(_Val)>(_Val));};
#define bind_del(p, method) p._Meta._Deleter = [this] {method();};

#define unlock_property(p) p._Meta._Unlock(); {
#define lock_property(p) } p._Meta._Lock();
#define verify_lock                                                   \
    if (_Meta._Locked)                                                \
    {                                                                 \
        const char* _Err_msg = "Property raw value not accessible\n"; \
        std::cerr << _Err_msg;                                        \
        throw std::runtime_error{_Err_msg};                           \
    }

namespace ext::detail {template <typename _Tx, bool ce_reactions> class meta_property;}
namespace ext {template <typename _Tx, bool ce_reactions = false> class property;}

#include <functional>
#include <tuple>

#include <ext/boolean.hpp>
#include <ext/keywords.hpp>
#include <ext/number.hpp>
#include <ext/set.hpp>
#include <ext/type_traits.hpp>


template <typename _Tx, bool ce_reactions>
class ext::detail::meta_property
{
public aliases:
    using qt_method_t     = std::function<void(_Tx)>;
    using qt_method_set_t = ext::set<qt_method_t>;

    using getter_t  = std::function<_Tx()>;
    using setter_t  = std::function<void(_Tx)>;
    using deleter_t = std::function<void()>;

public friends:
    friend class ext::property<_Tx, ce_reactions>;

public cpp_methods:
    auto _Unlock() -> void {_Locked = false;};
    auto _Lock() -> void {_Locked = true;};
    auto _Attach_clamp(_Tx&& _Low, _Tx&& _High) -> void requires std::is_arithmetic_v<_Tx>;
    template <typename ..._Valty> auto _Attach_constraint(_Valty&&... _Allowed) -> void;
    template <typename _Ty, typename ..._Valty> auto _Attach_qt_method(_Ty _Qt_obj, _Valty&&... _Callbacks) -> void;

public cpp_properties:
    getter_t  _Getter  = [this] {return _Val;};
    setter_t  _Setter  = [this](auto&& _Other) {_Val = std::forward<decltype(_Other)>(_Other);};
    deleter_t _Deleter = [this]() {if constexpr(std::is_pointer_v<_Tx>) {delete _Val; _Val = nullptr;}};

private cpp_methods:
    auto _Is_value_valid(_Tx _That) const -> std::tuple<ext::boolean, _Tx>;
    auto _Is_value_valid(_Tx _That) const -> std::tuple<ext::boolean, _Tx> requires ext::is_template_base_of_v<_Tx, ext::number>;

private cpp_properties:
    _Tx _Val;
    ext::boolean _Locked {true};

    struct {ext::boolean _Is; std::pair<int, int> _Range    ;} _Clamp;
    struct {ext::boolean _Is; ext::set<_Tx>       _Allowed  ;} _Constraints;
    struct {ext::boolean _Is; qt_method_set_t     _Callbacks;} _Qt_callbacks;
};


template <typename _Tx, bool ce_reactions>
auto ext::detail::meta_property<_Tx, ce_reactions>::_Attach_clamp(_Tx&& _Low, _Tx&& _High) -> void requires std::is_arithmetic_v<_Tx>
{
    // set the clamp and add the range to it
    _Clamp._Is = true;
    _Clamp._Range = {_Low, _High};
}


template <typename _Tx, bool ce_reactions>
template <typename ..._Valty>
auto ext::detail::meta_property<_Tx, ce_reactions>::_Attach_constraint(_Valty&&... _Allowed) -> void
{
    // set the constraints and add the allowed values to it
    _Constraints._Is    = true;
    _Constraints._Range = ext::set{std::forward<_Valty>(_Allowed)...};
}


template <typename _Tx, bool ce_reactions>
template <typename _Ty, typename ..._Valty>
auto ext::detail::meta_property<_Tx, ce_reactions>::_Attach_qt_method(_Ty _Qt_obj, _Valty&&... _Callbacks) -> void
{
    // set the of qt callbacks and add all the callbacks to it
    _Qt_callbacks._Is = true;
    _Qt_callbacks._Callbacks = ext::set{std::bind_front(std::forward<_Valty>(_Callbacks), _Qt_obj)...};
}


template <typename _Tx, bool ce_reactions>
auto ext::detail::meta_property<_Tx, ce_reactions>::_Is_value_valid(_Tx _That) const -> std::tuple<ext::boolean, _Tx>
{
    // for non-arithmetic types, check that the constraints are satisfied
    return {_Constraints._Is and _Constraints._Allowed.contains(_That), _That};
}


template <typename _Tx, bool ce_reactions>
auto ext::detail::meta_property<_Tx, ce_reactions>::_Is_value_valid(_Tx _That) const -> std::tuple<ext::boolean, _Tx> requires ext::is_template_base_of_v<_Tx, ext::number>
{
    // for arithmetic types, check that the constraints are satisfied, and then clamp the value
    if (_Constraints._Is and not _Constraints._Allowed.contains(_That)) return {false, _That};
    if (_Clamp._Is) return {true, std::clamp(_That, _Clamp._Range.first, _Clamp._Range.second)};
    return {true, _That};
}


#endif //SBROWSER2_META_PROPERTY_HPP
