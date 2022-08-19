#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_MEMORY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_MEMORY_HPP

#include "dom_object.hpp"
namespace web_assembly::js {class memory;}

#include USE_INNER_TYPES(web_assembly_js)
#include <v8-forward.h>


class web_assembly::js::memory
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(memory);
    memory() = default;
    memory(detail::memory_descriptor_t&& descriptor);

public js_methods:
    auto grow(const ext::number<ulong>& delta) -> ext::number<ulong>;

public js_properties:
    ext::property<v8::ArrayBuffer> buffer;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_MEMORY_HPP
