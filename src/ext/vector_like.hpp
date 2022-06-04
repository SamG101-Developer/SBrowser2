#pragma once
#ifndef SBROWSER2_VECTOR_LIKE_HPP
#define SBROWSER2_VECTOR_LIKE_HPP

namespace ext {template <typename _Tx1> class vector_like;}

#include <ext/keywords.hpp>
#include <ext/number.hpp>
#include <ext/property.hpp>
#include <ext/vector.hpp>


template <typename _Tx1>
class ext::vector_like
{
public constructors:
    explicit vector_like(ext::vector<_Tx1>* _Container) : _LinkedContainer{_Container} {bind_get(length, _LinkedContainer.size);};

public cpp_properties:
    property<number<size_t>> length;

public cpp_operators:
    auto operator[](const number<size_t>& _Idx) -> optional<_Tx1&> {return _LinkedContainer->at(_Idx);};

private cpp_properties:
    std::shared_ptr<ext::vector<_Tx1>> _LinkedContainer;
};


#endif //SBROWSER2_VECTOR_LIKE_HPP
