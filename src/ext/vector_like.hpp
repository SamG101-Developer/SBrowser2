#pragma once
#ifndef SBROWSER2_VECTOR_LIKE_HPP
#define SBROWSER2_VECTOR_LIKE_HPP

#include "ext/keywords.hpp"
#include "ext/number.hpp"
#include "ext/property.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"


_EXT_BEGIN

template <typename T>
class vector_like
{
public constructors:
    vector_like()
    {bind_get(length);}

public cpp_operators:
    virtual auto operator[](const number<size_t>& index) -> T& = 0;
    virtual auto operator[](ext::string_view index) -> T& = 0;

public cpp_properties:
    property<number<size_t>> length;

protected cpp_accessors:
    virtual DEFINE_GETTER(length) = 0;
};


template <typename T>
class vector_like_linked : public vector_like<T>
{
public constructors:
    explicit vector_like_linked(vector<T>* container) : linked_vector{container}
    {bind_get(length);}

public cpp_operators:
    auto operator[](const number<size_t>& index) -> T& override {return linked_vector->at(index);}
    auto operator[](ext::string_view index) -> T& override {return linked_vector->front();};

private cpp_properties:
    std::unique_ptr<vector<T>> linked_vector;

private cpp_accessors:
    DEFINE_GETTER(length) override {return linked_vector->size();}
};

_EXT_END


#endif //SBROWSER2_VECTOR_LIKE_HPP
