module;
#include "ext/macros.hpp"
#include <v8-forward.h>


export module ext.mixins:async_like;

#if USE_MODULES
    import ext.core;
    import ext.js;
#else
    #include "ext/impl/any.ixx"
    #include "ext/impl/vector.ixx"
    #include "ext/impl/promise.ixx"
#endif


_EXT_BEGIN
    export class async_like;
    export class async_like_private;
_EXT_END


class ext::async_like_private
{
public:
    virtual auto asynchronous_iterator_initialization_steps(v8::Local<v8::Object> iterator, ext::vector<ext::any> args) -> void = 0;
    virtual auto get_next_iteration_result(v8::Local<v8::Object> iterator) -> ext::promise<ext::any> = 0;
    virtual auto asynchronous_iterator_return_steps(v8::Local<v8::Object> iterator, v8::Local<v8::Object> arg) -> ext::promise<void> = 0;
};


class ext::async_like {};
