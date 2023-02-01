#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_MODULE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_MODULE_HPP


namespace web_assembly::js {class module;}


#include "ext/vector.hpp"
#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(web_assembly_js)


class web_assembly::js::module
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(module);
    module() = default;
    explicit module(v8::Local<v8::ArrayBuffer> bytes);

private js_methods:
    static auto exports(module* module_object) -> ext::vector<detail::module_export_descriptor_t>;
    static auto imports(module* module_object) -> ext::vector<detail::module_import_descriptor_t>;
    static auto custom_sections(module* module_object, ext::string_view section_name) -> ext::vector<v8::Local<v8::ArrayBuffer>>;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_MODULE_HPP
