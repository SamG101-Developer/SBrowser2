#pragma once
#ifndef SBROWSER2_VECTOR_LIKE_HPP
#define SBROWSER2_VECTOR_LIKE_HPP

namespace ext {template <typename _Tx1> class vector_like;}

#include <ext/keywords.hpp>
#include <ext/number.hpp>
#include <ext/property.hpp>
#include <ext/shared_pointer.hpp>
#include <ext/vector.hpp>


template <typename _Tx1>
class ext::vector_like
{
public constructors:
    explicit vector_like(ext::vector<_Tx1>* _Container) : _Linked_container{_Container} {bind_get(length, _Linked_container.size);};

public cpp_properties:
    property<number<size_t>> length;

public cpp_operators:
    auto operator[](const number<size_t>& _Idx) -> optional<_Tx1&> {return _Linked_container->at(_Idx);};

private cpp_properties:
    shared_pointer<ext::vector<_Tx1>> _Linked_container;
};


#endif //SBROWSER2_VECTOR_LIKE_HPP
