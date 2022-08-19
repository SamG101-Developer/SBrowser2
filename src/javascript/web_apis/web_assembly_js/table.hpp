#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_TABLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_TABLE_HPP

#include "dom_object.hpp"
#include "ext/vector_like.hpp"
namespace web_assembly::js {class table;}

#include USE_INNER_TYPES(web_assembly_js)


class web_assembly::js::table
        : public virtual dom_object
        , public ext::vector_like<ext::any>
{
public constructors:
    DOM_CTORS(table);
    table() = default;
    table(detail::table_escriptor_t&& descriptor, const ext::any& value = nullptr);

public js_methods:
    auto grow(const ext::number<ulong>& delta, const ext::any& value = nullptr) -> ext::number<ulong>;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_TABLE_HPP
