#include "svg_animated_boolean.hpp"
#include "svg_animated_boolean_private.hpp"


auto svg::types::svg_animated_boolean::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<svg::types::svg_animated_boolean>{isolate}
        .inherit<svg_abstract_animatable<ext::boolean>>()
        .auto_wrap_objects();

    return std::move(conversion);
}
