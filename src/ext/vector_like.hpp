#pragma once
#ifndef SBROWSER2_VECTOR_LIKE_HPP
#define SBROWSER2_VECTOR_LIKE_HPP

namespace ext {template <typename _Tx> class vector_like;}

#include "ext/keywords.hpp"
#include "ext/number.hpp"
#include "ext/property.hpp"
#include "ext/vector.hpp"


template <typename _Tx>
class ext::vector_like
{
public constructors:
    explicit vector_like(ext::vector<_Tx>* _Container) : _LinkedContainer{_Container} {bind_get(length);};

public cpp_properties:
    property<number<size_t>> length;

public cpp_operators:
    auto operator[](const number<size_t>& _Idx) -> optional<_Tx&> {return _LinkedContainer->at(_Idx);};

private cpp_properties:
    std::shared_ptr<ext::vector<_Tx>> _LinkedContainer;

private cpp_accessors:
    [[nodiscard]] auto get_length() const -> ext::number<size_t> {return _LinkedContainer->size();};
};


#endif //SBROWSER2_VECTOR_LIKE_HPP
