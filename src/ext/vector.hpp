#pragma once
#ifndef SBROWSER2_VECTOR_HPP
#define SBROWSER2_VECTOR_HPP

#include <veque.hpp>
#include <ext/type_traits.hpp>

namespace     {template <typename _Vt> using vector_internal = veque::veque<_Vt>;}
namespace ext {template <typename _Tx> class vector;}
namespace ext {template <typename _Vt> using vector_view = vector<_Vt>;}

namespace ext {using string_vector = ext::vector<ext::string>;}
namespace ext {using string_vector_view = const ext::vector<ext::string>&;}

#include <ranges>
#include <ext/keywords.hpp>
#include <ext/optional.hpp>

template <typename _Tx>
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

public constructors:
    using vector_internal<_Tx>::vector_internal;

    vector(all_same_as<_Tx> auto&&... _Val)
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

    auto operator+=(iterable auto _Other) -> vector&
    {
        this->reserve(_Other.size());
        for (const auto& _Item: _Other)
            this->push_back(_Item);
        return *this;
    }

    auto operator+ (iterable auto _Other) -> vector
    {
        vector<_Tx> _Out{this->size() + _Other.size()};
        _Out += *this;
        _Out += _Other;
        return _Out;
    }
};


#endif //SBROWSER2_VECTOR_HPP
