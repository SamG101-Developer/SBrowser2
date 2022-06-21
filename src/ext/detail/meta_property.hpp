#pragma once
#ifndef SBROWSER2_META_PROPERTY_HPP
#define SBROWSER2_META_PROPERTY_HPP

#include <ext/set.hpp>

#define bind_get(p) p._Meta._Getter  = [this] {return get_##p();}
#define bind_set(p) p._Meta._Setter  = [this](auto&& _Any) {set_##p(std::forward<decltype(_Any)>(_Any));}
#define bind_del(p) p._Meta._Deleter = [this] {del_##p();}

#define bind_qt(p, widget, method) p._Meta._AttachQtMethod(widget, &method);

#define is_smart_property (ext::is_smart_pointer_v<outer_val_t>)
#define is_dumb_property (!is_smart_property)

#define unlock_property(p) p._Meta._Unlock()
#define lock_property(p) p._Meta._Lock()
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
public constructors:
    explicit meta_property() = default;
    explicit meta_property(const _Tx& _That) : _Val{_That} {}
    explicit meta_property(_Tx&& _That) : _Val(std::forward<_Tx>(_That)) {};

public aliases:
    using outer_val_t = _Tx;
    using inner_val_t = unwrap_smart_pointer_t<outer_val_t>;

    using qt_method_t     = std::function<void(inner_val_t)>;
    using qt_method_set_t = ext::set<qt_method_t>;

    using getter_t  = std::function<inner_val_t()>;
    using setter_t  = std::function<void(inner_val_t)>;
    using deleter_t = std::function<void()>;

public friends:
    friend class ext::property<_Tx, ce_reactions>;

public cpp_methods:
    auto _Unlock() -> void {_Locked = false;};
    auto _Lock() -> void {_Locked = true;};

    auto _AttachClamp(_Tx&& _Low, _Tx&& _High) -> void requires std::is_arithmetic_v<_Tx>;
    template <typename ..._Valty> auto _AttachConstraint(_Valty&&... _Allowed) -> void;
    template <typename _Ty, typename _Ty2> auto _AttachQtMethod(_Ty _Qt_obj, _Ty2&& _Callback) -> void;

public cpp_properties:
    getter_t _Getter = [this]
    {
        if constexpr is_dumb_property
            return _Val;
        else
            return _Val.get();
    };

    setter_t _Setter = [this](auto&& _Other)
    {
        if constexpr is_dumb_property
            _Val = std::forward<decltype(_Other)>(_Other);
        else
            _Val.reset(_Other);
    };

    deleter_t _Deleter = [this]()
    {
        if constexpr is_smart_property
            _Val.release();
    };

private cpp_methods:
    auto _IsValueValid(_Tx _That) const -> std::tuple<ext::boolean, _Tx>;
    auto _IsValueValid(_Tx _That) const -> std::tuple<ext::boolean, _Tx> requires ext::is_template_base_of_v<_Tx, ext::number>;

public cpp_properties:
    _Tx _Val;
    ext::boolean _Locked {true};

    struct {ext::boolean _Is; std::pair<int, int> _Range    ;} _Clamp;
    struct {ext::boolean _Is; ext::set<_Tx>       _Allowed  ;} _Constraints;
    struct {ext::boolean _Is; qt_method_set_t     _Callbacks;} _Qt_callbacks;
};


template <typename _Tx, bool ce_reactions>
auto ext::detail::meta_property<_Tx, ce_reactions>::_AttachClamp(_Tx&& _Low, _Tx&& _High) -> void requires std::is_arithmetic_v<_Tx>
{
    // set the clamp and add the range to it
    _Clamp._Is = true;
    _Clamp._Range = {_Low, _High};
}


template <typename _Tx, bool ce_reactions>
template <typename ..._Valty>
auto ext::detail::meta_property<_Tx, ce_reactions>::_AttachConstraint(_Valty&&... _Allowed) -> void
{
    // set the constraints and add the allowed values to it
    _Constraints._Is    = true;
    _Constraints._Range = ext::set{std::forward<_Valty>(_Allowed)...};
}


template <typename _Tx, bool ce_reactions>
template <typename _Ty, typename _Ty2>
auto ext::detail::meta_property<_Tx, ce_reactions>::_AttachQtMethod(_Ty _Qt_obj, _Ty2&& _Callback) -> void
{
    // set the of qt callbacks and add the callbacks to it (can be called multiple times)
    _Qt_callbacks._Is = true;
    _Qt_callbacks._Callbacks.emplace([this, &_Qt_obj, _Callback = std::forward<_Ty>(_Callback)] {std::mem_fn(_Callback)(_Qt_obj, _Val);});
}


template <typename _Tx, bool ce_reactions>
auto ext::detail::meta_property<_Tx, ce_reactions>::_IsValueValid(_Tx _That) const -> std::tuple<ext::boolean, _Tx>
{
    // for non-arithmetic types, check that the constraints are satisfied
    return {_Constraints._Is and _Constraints._Allowed.contains(_That), _That};
}


template <typename _Tx, bool ce_reactions>
auto ext::detail::meta_property<_Tx, ce_reactions>::_IsValueValid(_Tx _That) const -> std::tuple<ext::boolean, _Tx> requires ext::is_template_base_of_v<_Tx, ext::number>
{
    // for arithmetic types, check that the constraints are satisfied, and then clamp the value
    if (_Constraints._Is && not _Constraints._Allowed.contains(_That)) return {false, _That};
    if (_Clamp._Is) return {true, std::clamp(_That, _Clamp._Range.first, _Clamp._Range.second)};
    return {true, _That};
}


#endif //SBROWSER2_META_PROPERTY_HPP
