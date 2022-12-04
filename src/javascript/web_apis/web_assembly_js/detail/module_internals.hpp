#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_MODULE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_MODULE_INTERNALS_HPP

#include "ext/vector.hpp"
#include "ext/promise.ixx"
#include <v8-wasm.h>
#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(web_assembly_js)
namespace web_assembly::js {class instance;}
namespace web_assembly::js {class module;}


namespace web_assembly::detail
{
    auto compile_web_assembly_module(
            v8::Local<v8::ArrayBuffer> bytes)
            -> js::module;

    auto construct_web_assembly_module_object(
            v8::Local<v8::WasmModuleObject> module,
            v8::Local<v8::ArrayBuffer> bytes)
            -> js::module;

    auto asynchronously_compile_web_assembly_module(
            v8::Local<v8::ArrayBuffer> bytes
            /* TODO : optional task source */)
            -> ext::promise<js::module>;

    auto read_imports(
            v8::Local<v8::WasmModuleObject> module,
            v8::Local<v8::Object> import_objects)
            -> void; /* TODO : return type */

    auto create_exports_object(
            v8::Local<v8::WasmModuleObject> module,
            js::instance* instance)
            -> v8::Object;

    auto initialize_instance_object(
            v8::Local<v8::Object> instance_object,
            v8::Local<v8::WasmModuleObject> module,
            js::instance* instance)
            -> void;

    auto instantiate_core_of_web_assembly_module(
            js::module* module,
            ext::vector<v8::Local<v8::Object>> imports)
            -> void;

    auto asynchronously_instantiate_core_of_web_assembly_module(
            js::module* module,
            ext::vector<v8::Local<v8::Object>> imports)
            -> void;

    auto instantiate_web_assembly_module(
            js::module* module,
            ext::vector<v8::Local<v8::Object>> imports)
            -> js::instance;

    auto instantiate_promise_of_module(
            ext::promise<js::module*> promise_of_module,
            ext::vector<v8::Local<v8::Object>> imports)
            -> ext::promise<web_assembly_instantiated_source_t>;

    template <typename T>
    auto string_value_of_extern_type()
            -> ext::string;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_MODULE_INTERNALS_HPP
