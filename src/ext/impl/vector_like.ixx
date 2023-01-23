module;
#include "ext/macros/namespaces.hpp"
#include "ext/macros.hpp"


export module ext.mixins:vector_like;
import ext.core;
import apis.dom_object;
import js.env.module_type;
import :async_like;


export namespace ext
{
    template <typename T> class vector_like;
    template <typename T> class vector_like_linked;

    template <typename T> class vector_like_private;
    template <typename T> class vector_like_linked_private;

    template <typename T> class async_vector_like;
    template <typename T> class async_vector_like_private;
}


export template <typename T>
class ext::vector_like_private : virtual dom_object_private
{
public:
    MAKE_QIMPL_T(vector_like, T);
};


export template <typename T>
class ext::vector_like_linked_private : vector_like_private<T>
{
public:
    MAKE_QIMPL_T(vector_like_linked, T);

public:
    std::unique_ptr<vector<T>> linked_vector;
};


export template <typename T>
class async_vector_like_private
        : public vector_like_private
        , public async_like_private
{
public:
    MAKE_QIMPL_T(vasync_vector_like, T);
};


export template <typename T>
class ext::vector_like
        : public virtual dom_object
{
public constructors:
    MAKE_PIMPL_T(vector_like, T);
    MAKE_V8_AVAILABLE(ALL);
    explicit vector_like() {INIT_PIMPL;}

public:
    virtual auto operator[](number<size_t> index) -> T& = 0;
    virtual auto operator[](number<size_t> index) const -> T& = 0;
    virtual auto operator[](ext::string_view index) -> T& = 0;
    virtual auto operator[](ext::string_view index) const -> T& = 0;

protected js_properties:
    virtual DEFINE_GETTER(length, ext::number<size_t>) = 0;
};


export template <typename T>
class ext::vector_like_linked
        : public vector_like<T>
{
public constructors:
    MAKE_PIMPL_T(vector_like_linked, T);
    MAKE_V8_AVAILABLE(ALL);

    explicit vector_like_linked(vector<T>* container = nullptr)
    {
        INIT_PIMPL; ACCESS_PIMPL;
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


export template <typename T>
class ext::async_vector_like
{
public:
    MAKE_PIMPL_T(async_vector_like, T);
    MAKE_V8_AVAILABLE(ALL);
    explicit async_vector_like() {INIT_PIMPL;}
};
