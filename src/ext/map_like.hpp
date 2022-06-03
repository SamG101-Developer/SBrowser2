#pragma once
#ifndef SBROWSER2_MAP_LIKE_HPP
#define SBROWSER2_MAP_LIKE_HPP

namespace ext {template <typename _Tx1, typename _Tx2> class map_like;}

#include <ext/keywords.hpp>
#include <ext/optional.hpp>
#include <ext/map.hpp>


template <typename _Tx1, typename _Tx2>
class ext::map_like
{
public constructors:
    explicit map_like(ext::map<_Tx2, _Tx1>* _Container) : _Linked_container{_Container} {};

public cpp_operators:
    auto operator[](const _Tx1& _Key) -> optional<_Tx2> {return _Linked_container.at(_Key);}

private cpp_properties:
    shared_pointer<ext::map<_Tx1, _Tx2>> _Linked_container;
};


#endif //SBROWSER2_MAP_LIKE_HPP
