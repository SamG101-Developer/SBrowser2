#pragma once
#ifndef SBROWSER2_VECTOR_LIKE_HPP
#define SBROWSER2_VECTOR_LIKE_HPP

#include "ext/keywords.ixx"
#include "ext/number.ixx"
#include "ext/pimpl.ixx"
#include "ext/property.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS_TEMPLATED(ext, vector_like, typename T) : virtual dom_object_private {};


DEFINE_PRIVATE_CLASS_TEMPLATED(ext, vector_like_linked, typename T) : vector_like_private<T>
{
    std::unique_ptr<vector<T>> linked_vector;
};



_EXT_BEGIN

template <typename T>
class vector_like : public virtual dom_object
{
public constructors:
    MAKE_PIMPL_TEMPLATED(vector_like, T);
    MAKE_V8_AVAILABLE;

    explicit vector_like()
    {INIT_PIMPL_TEMPLATED(vector_like, T);}

public:
    virtual auto operator[](number<size_t> index) -> T& = 0;
    virtual auto operator[](number<size_t> index) const -> T& = 0;
    virtual auto operator[](ext::string_view index) -> T& = 0;
    virtual auto operator[](ext::string_view index) const -> T& = 0;

protected js_properties:
    virtual DEFINE_GETTER(length, ext::number<size_t>) = 0;
};


template <typename T>
class vector_like_linked : public vector_like<T>
{
public constructors:
    MAKE_PIMPL_TEMPLATED(vector_like_linked, T);
    MAKE_V8_AVAILABLE;

    explicit vector_like_linked(vector<T>* container = nullptr)
    {
        INIT_PIMPL_TEMPLATED(vector_like_linked, T);
        ACCESS_PIMPL_TEMPLATED(vector_like_linked, T);
        d->linked_vector = container ? std::unique_ptr<vector<T>>{container} : std::make_unique<vector<T>>();
    }

public:
    auto operator[](number<size_t> index) -> T& override
    {
        ACCESS_PIMPL_TEMPLATED(vector_like_linked, T);
        return d->linked_vector->at(index);
    }

    auto operator[](number<size_t> index) const -> T& override
    {
        ACCESS_PIMPL_TEMPLATED(const vector_like_linked, T);
        return d->linked_vector->at(index);
    }

    auto operator[](ext::string_view index) -> T& override
    {
        ACCESS_PIMPL_TEMPLATED(vector_like_linked, T);
        return d->linked_vector->front(); // TODO
    };

    auto operator[](ext::string_view index) const -> T& override
    {
        ACCESS_PIMPL_TEMPLATED(const vector_like_linked, T);
        return d->linked_vector->front(); // TODO
    };

private js_properties:
    DEFINE_GETTER(length, ext::number<size_t>) override
    {
        ACCESS_PIMPL_TEMPLATED(const vector_like_linked, T);
        return d->linked_vector->size();
    }
};

_EXT_END


#endif //SBROWSER2_VECTOR_LIKE_HPP
