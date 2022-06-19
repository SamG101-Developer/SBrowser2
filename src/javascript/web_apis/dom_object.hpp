#ifndef SBROWSER2_DOM_OBJECT_HPP
#define SBROWSER2_DOM_OBJECT_HPP

#include <memory>

#include <ext/any.hpp>
#include <ext/custom_operator.hpp>
#include <ext/keywords.hpp>
#include <ext/property.hpp>
#include <ext/string.hpp>
#include <v8-isolate.h>
#include <v8pp/class.hpp>

namespace web_apis {class dom_object;}


class web_apis::dom_object
{
public constructors:
    dom_object() = default;
    dom_object(const dom_object&) = default;
    dom_object(dom_object&&) noexcept = default;
    auto operator=(const dom_object&) -> dom_object& = default;
    auto operator=(dom_object&&) noexcept -> dom_object& = default;
    virtual ~dom_object() = default;

public cpp_methods:
    virtual auto to_v8(v8::Isolate* isolate) const && -> ext::any = 0;
};


inline auto web_apis::dom_object::to_v8(v8::Isolate* isolate) const && -> ext::any
{
    return v8pp::class_<dom_object>{isolate}.auto_wrap_objects();
}


#endif //SBROWSER2_DOM_OBJECT_HPP
