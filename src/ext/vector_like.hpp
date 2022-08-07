#pragma once
#ifndef SBROWSER2_VECTOR_LIKE_HPP
#define SBROWSER2_VECTOR_LIKE_HPP

#include "ext/keywords.hpp"
#include "ext/number.hpp"
#include "ext/property.hpp"
#include "ext/vector.hpp"


_EXT_BEGIN


template <typename T>
class vector_like
{
public cpp_operators:
    virtual auto operator[](const number<size_t>& _Idx) -> T& = 0;
};

template <typename _Tx>
class vector_like_linked : public vector_like<_Tx>
{
public constructors:
    explicit vector_like_linked(vector<_Tx>* _Container) : _LinkedContainer{_Container} {bind_get(length);};

public cpp_properties:
    property<number<size_t>> length;

public cpp_operators:
    auto operator[](const number<size_t>& _Idx) -> _Tx& {return _LinkedContainer->at(_Idx);};

private cpp_properties:
    std::unique_ptr<vector<_Tx>> _LinkedContainer;

private cpp_accessors:
    [[nodiscard]] auto get_length() const -> number<size_t> {return _LinkedContainer->size();};
};


_EXT_END


#endif //SBROWSER2_VECTOR_LIKE_HPP
