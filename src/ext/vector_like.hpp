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
    virtual auto operator[](const number<size_t>& index) -> T& = 0;
};


template <typename T>
class vector_like_linked : public vector_like<T>
{
public constructors:
    explicit vector_like_linked(vector<T>* container)
            : linked_vector{container}
    {bind_get(length);}

public cpp_properties:
    property<number<size_t>> length;

public cpp_operators:
    auto operator[](const number<size_t>& index) -> T& {return linked_vector->at(index);}

private cpp_properties:
    std::unique_ptr<vector<T>> linked_vector;

private cpp_accessors:
    [[nodiscard]] auto get_length() const -> number<size_t> {return linked_vector->size();}
};

_EXT_END


#endif //SBROWSER2_VECTOR_LIKE_HPP
