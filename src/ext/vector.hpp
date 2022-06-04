#pragma once
#ifndef SBROWSER2_VECTOR_HPP
#define SBROWSER2_VECTOR_HPP

#include <veque.hpp>

namespace     {template <typename _Vt> using container_internal = veque::veque<_Vt>;}
namespace ext {template <typename _Tx> class vector;}

#include <ext/keywords.hpp>
#include <ext/optional.hpp>


template <typename _Tx>
class ext::vector
        : public container_internal<_Tx>
{
public aliases:
    using reference = typename container_internal<_Tx>::reference;
    using const_reference = typename container_internal<_Tx>::const_reference;
    using value_type = _Tx;
    using size_type = typename container_internal<_Tx>::size_type;

public constructors:
    vector() = default;

    vector(const vector&) = default;
    vector(vector&&) noexcept = default;
    auto operator=(const vector&) -> vector& = default;
    auto operator=(vector&&) noexcept -> vector& = default;

    vector(size_type _N, const _Tx& _Val) : veque::veque<_Tx>{_N, _Val} {};
    vector(size_type _N, _Tx&& _Val) : veque::veque<_Tx>{_N, std::forward<_Tx>(_Val)} {};
    template <typename ..._Valty> vector(_Valty... _Val) : veque::veque<_Tx>{std::initializer_list{std::forward<_Valty>(_Val)...}} {};

public cpp_methods:
    auto front()       -> optional<      reference> {return (*this)[0];};
    auto front() const -> optional<const_reference> {return (*this)[0];};

    auto back()       -> optional<      reference> {return (*this)[this->size() - 1];};
    auto back() const -> optional<const_reference> {return (*this)[this->size() - 1];};

    auto at(size_type _Idx)       -> optional<      reference> {return (*this)[_Idx];};
    auto at(size_type _Idx) const -> optional<const_reference> {return (*this)[_Idx];};

public cpp_operators:
    auto operator[](size_type _Idx)       -> optional<      reference> {return optional{this->begin() + _Idx != nullptr ? this->begin() + _Idx : null};};
    auto operator[](size_type _Idx) const -> optional<const_reference> {return optional{this->begin() + _Idx != nullptr ? this->begin() + _Idx : null};};
};


#endif //SBROWSER2_VECTOR_HPP
