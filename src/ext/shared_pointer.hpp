#pragma once
#ifndef SBROWSER2_SHARED_POINTER_HPP
#define SBROWSER2_SHARED_POINTER_HPP

namespace ext {template <typename _Tx> class shared_pointer;}
namespace ext {template <typename _Ty, typename ..._Valty> auto make_shared(_Valty&&... _Val) -> shared_pointer<_Ty>;}

#include <utility>
#include <ext/keywords.hpp>


template <typename _Tx>
class ext::shared_pointer
{
public:
    using pointer_t = _Tx;

public:
    shared_pointer() : _Ptr{nullptr}, _Ctr{nullptr} {};
    explicit shared_pointer(_Tx* _Other) : _Ptr{_Other}, _Ctr{new counter{}} {_Ctr->_Add_reference();};
    ~shared_pointer() {_Rel();};

    shared_pointer(const shared_pointer& _Other) {_Cpy_Ptr(_Other);};
    shared_pointer(shared_pointer&& _Other) noexcept {_Mov_Ptr(std::forward<shared_pointer>(_Other));};
    auto operator=(const shared_pointer& _Other) -> shared_pointer&;
    auto operator=(shared_pointer&& _Other) noexcept -> shared_pointer&;

public:
    [[nodiscard]] auto is_unique() const -> bool {return _Ctr->_Get_reference() == 1;};
    auto get() const -> _Tx* {return _Ptr;};
    auto reset() const -> void {_Ptr = nullptr;};
    auto swap(shared_pointer& _Other) noexcept -> decltype(auto);

public:
    auto operator*() const -> _Tx& {return _Ptr;};
    auto operator->() const -> _Tx* {return _Ptr;};
    auto operator<=>(const shared_pointer& _Other) const -> bool {return _Ptr <=> _Other->_Ptr;};
    operator bool() const {return _Ptr != nullptr;};
    operator _Tx*() const {return _Ptr;};

private:
    class counter
    {
    public:
        template <typename _Vt> friend class shared_pointer;

    private:
        [[nodiscard]] auto _Get_reference() const -> size_t {return _Ctr;};

        auto _Add_reference() -> size_t {++_Ctr;};
        auto _Del_reference() -> size_t {--_Ctr;};

    private:
        size_t _Ctr;
    };

private:
    auto _Rel();
    auto _Cpy_Ptr(const shared_pointer& _Other) -> void;
    auto _Mov_Ptr(shared_pointer&& _Other) noexcept -> void;

private:
    _Tx* _Ptr;
    counter* _Ctr;
};


template <typename _Tx>
inline auto ext::shared_pointer<_Tx>::operator=(const shared_pointer& _Other) -> shared_pointer&
{
    // release and copy the other pointer if it exists and is different to the current pointer
    if (_Other._Ptr and _Ptr != _Other._Ptr) {_Rel(); _Cpy_Ptr(_Other);}
    return *this;
}


template <typename _Tx>
inline auto ext::shared_pointer<_Tx>::operator=(shared_pointer&& _Other) noexcept -> shared_pointer&
{
    // release and move the other pointer if it exists and is different to the current pointer
    if (_Other._Ptr and _Ptr != _Other._Ptr) {_Rel(); _Mov_Ptr(std::forward<shared_pointer>(_Other));}
    return *this;
}


template <typename _Tx>
inline auto ext::shared_pointer<_Tx>::swap(shared_pointer<_Tx>& _Other) noexcept -> decltype(auto)
{
    // swap the pointer and counter between the shared pointer objects
    std::swap(_Ptr, _Other._Ptr);
    std::swap(_Ctr, _Other._Ctr);
}


template <typename _Tx>
inline auto ext::shared_pointer<_Tx>::_Rel()
{
    // if the post deletion counter is at 0, delete and set the pointer and counter to nullptr
    if (_Ctr and _Ctr->_Del_reference() == 0)
    {
        delete _Ptr; _Ptr = nullptr;
        delete _Ctr; _Ctr = nullptr;
    }
}


template <typename _Tx>
auto ext::shared_pointer<_Tx>::_Cpy_Ptr(const shared_pointer<_Tx>& _Other) -> void
{
    // copy the pointer and counter by reference, and increment the counter's counter
    _Ptr = _Other._Ptr;
    _Ctr = _Other._Ctr;
    _Ctr->_Add_reference();
}


template <typename _Tx>
auto ext::shared_pointer<_Tx>::_Mov_Ptr(shared_pointer<_Tx>&& _Other) noexcept -> void
{
    // move the pointer and counter, and release the other pointer (no counter increment)
    _Ptr = std::move(_Other._Ptr);
    _Ctr = std::move(_Other._Ctr);
    _Other._Rel();
}


template <typename _Ty, typename ..._Valty> auto ext::make_shared(_Valty&&... _Val) -> shared_pointer<_Ty>
{
    // construct a new shared pointer by forwarding the arguments into a raw pointer and wrapping in a shared pointer
    return shared_pointer{new _Ty{std::forward<_Valty>(_Val)...}};
}


#endif //SBROWSER2_SHARED_POINTER_HPP
