#pragma once
#ifndef SBROWSER2_VECTOR_HPP
#define SBROWSER2_VECTOR_HPP

#include "ext/type_traits.hpp"
#include <veque.hpp>
#include <v8-container.h>

namespace     {template <typename _Vt> using vector_internal = veque::veque<_Vt>;}
namespace ext {template <typename _Tx, typename _Tx1 = v8::Array> class vector;}
namespace ext {template <typename _Vt, typename _Tx1 = v8::Array> using vector_view = const vector<_Vt, _Tx1>&;}

namespace ext {using string_vector = ext::vector<ext::string>;}
namespace ext {using string_vector_view = const string_vector&;}

#include "ext/keywords.hpp"
#include "ext/optional.hpp"
#include <ranges>

template <typename _Tx, typename _Tx1>
class ext::vector
        : public vector_internal<_Tx>
{
public aliases:
    using reference = typename vector_internal<_Tx>::reference;
    using const_reference = typename vector_internal<_Tx>::const_reference;
    using value_type = _Tx;
    using size_type = typename vector_internal<_Tx>::size_type;

    using iterator = typename vector_internal<_Tx>::iterator;
    using const_iterator = typename vector_internal<_Tx>::const_iterator;

    using javascript_container_t = _Tx1;

public constructors:
    using vector_internal<_Tx>::vector_internal;

    vector(type_is<_Tx> auto&&... _Val)
    {
        (this->template emplace(std::forward<_Tx>(_Val)), ...);
    };

public cpp_methods:
    auto front() -> optional<value_type> {return (*this)[0];};
    auto front() const -> optional<const value_type> {return (*this)[0];};

    auto back() -> optional<value_type> {return (*this)[this->size() - 1];};
    auto back() const -> optional<const value_type> {return (*this)[this->size() - 1];};

    auto at(size_type _Idx) -> optional<value_type> {return (*this)[_Idx];};
    auto at(size_type _Idx) const -> optional<const value_type> {return (*this)[_Idx];};

    auto extend(const_iterator _Where, ext::vector_view<_Tx> _Other)
    {
        for (const auto& _Item: _Other | std::ranges::views::reverse)
            this->insert(_Where, _Item);
    }

public cpp_operators:
    auto operator[](size_type _Idx) -> optional<value_type> {if (this->begin() + _Idx != this->end()) return optional<value_type>{*(this->begin() + _Idx)}; else return optional<value_type>{};};
    auto operator[](size_type _Idx) const -> optional<const value_type> {if (this->begin() + _Idx != this->end()) return optional<value_type>{*(this->begin() + _Idx)}; else return optional<value_type>{};};

    auto operator+=(const iterable auto& _Other) -> vector&
    {
        this->reserve(_Other.size());
        for (const auto& _Item: _Other)
            this->push_back(_Item);
        return *this;
    }

    auto operator+(const iterable auto& _Other) -> vector
    {
        vector<_Tx> _Out{this->size() + _Other.size()};
        _Out += *this;
        _Out += _Other;
        return _Out;
    }
};


#endif //SBROWSER2_VECTOR_HPP
