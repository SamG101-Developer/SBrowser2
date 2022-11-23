#ifndef SBROWSER2_SRC_JAVASCRIPT_INTEROP_EXPOSE_MACROS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_INTEROP_EXPOSE_MACROS_HPP

#include "ext/enums.hpp"
#include "ext/number.hpp"
#include "ext/tuple.hpp"
#include "ext/type_traits.hpp"
#include "javascript/environment/environment_module.hpp"
#include <v8-isolate.h>
#include <v8pp/class.hpp>
#include <v8pp/convert.hpp>

#define V8_INTEROP_CREATE_JS_OBJECT                                                                    \
    return_if (~(E & _allowed_v8_environments)) ext::make_tuple(false, v8pp::class_<self_t>{nullptr}); \
    decltype(auto) v8_conversion = v8pp::class_<self_t>{isolate}

#define V8_INTEROP_EXTEND_JS_OBJECT(...) if (~(E & __VA_ARGS__)) v8_conversion

#define V8_INTEROP_SUCCESSFUL_CONVERSION ext::make_tuple(true, std::move(v8_conversion))

#define MAKE_V8_AVAILABLE(A)                                      \
    using enum js::env::module_t;                                 \
    inline static js::env::module_t _allowed_v8_environments = A; \
    static auto _to_v8(js::env::module_t E, v8::Isolate* isolate) -> ext::tuple<bool, v8pp::class_<self_t>>;


#endif //SBROWSER2_SRC_JAVASCRIPT_INTEROP_EXPOSE_MACROS_HPP
