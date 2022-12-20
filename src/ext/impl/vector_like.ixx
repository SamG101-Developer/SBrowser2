module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/namespaces.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"
#include <memory>


export module ext.mixins:vector_like;
import ext.core;
import apis.dom_object;
import apis.dom_object_private;
import js.env.module_type;


export DEFINE_PRIVATE_CLASS_T(ext, vector_like, typename T) : virtual dom_object_private {};


export DEFINE_PRIVATE_CLASS_T(ext, vector_like_linked, typename T) : vector_like_private<T>
{
    std::unique_ptr<vector<T>> linked_vector;
};


DEFINE_PUBLIC_CLASS_T(ext, vector_like, typename T)
        : public virtual dom_object
{
public constructors:
    MAKE_PIMPL_T(vector_like, T);
    MAKE_V8_AVAILABLE(ALL);

    explicit vector_like()
    {INIT_PIMPL;}

public:
    virtual auto operator[](number<size_t> index) -> T& = 0;
    virtual auto operator[](number<size_t> index) const -> T& = 0;
    virtual auto operator[](ext::string_view index) -> T& = 0;
    virtual auto operator[](ext::string_view index) const -> T& = 0;

protected js_properties:
    virtual DEFINE_GETTER(length, ext::number<size_t>) = 0;
};


DEFINE_PUBLIC_CLASS_T(ext, vector_like_linked, typename T)
        : public vector_like<T>
{
public constructors:
    MAKE_PIMPL_T(vector_like_linked, T);
    MAKE_V8_AVAILABLE(ALL);

    explicit vector_like_linked(vector<T>* container = nullptr)
    {
        INIT_PIMPL_TEMPLATED(vector_like_linked, T);
        ACCESS_PIMPL_TEMPLATED(vector_like_linked, T);
        d->linked_vector = container ? std::unique_ptr<vector<T>>{container} : std::make_unique<vector<T>>();
    }

public:
    auto operator[](number<size_t> index) -> T& override
    {
        ACCESS_PIMPL;
        return d->linked_vector->at(index);
    }

    auto operator[](number<size_t> index) const -> T& override
    {
        ACCESS_PIMPL;
        return d->linked_vector->at(index);
    }

    auto operator[](ext::string_view index) -> T& override
    {
        ACCESS_PIMPL;
        return d->linked_vector->front(); // TODO
    };

    auto operator[](ext::string_view index) const -> T& override
    {
        ACCESS_PIMPL;
        return d->linked_vector->front(); // TODO
    };

private js_properties:
    DEFINE_GETTER(length, ext::number<size_t>) override
    {
        ACCESS_PIMPL;
        return d->linked_vector->size();
    }
};
