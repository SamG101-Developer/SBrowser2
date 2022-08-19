#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_EXPORTED_FUNCTIONS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_EXPORTED_FUNCTIONS_INTERNALS_HPP

#include "ext/string.hpp"
#include "ext/vector.hpp"
#include <v8-forward.h>
#include <v8-platform.h>

namespace web_assembly::detail
{
    auto name_of_web_assembly_function(
            v8::Local<v8::VirtualAddressSpace> function_address)
            -> ext::string;

    auto create_new_exported_function(
            v8::Local<v8::VirtualAddressSpace> function_address)
            -> v8::Function;

    auto call_exported_function(
            v8::Local<v8::VirtualAddressSpace> function_address,
            ext::vector<v8::Local<v8::Value>> arguments)
            -> v8::Value;

    template <typename T>
    auto run_host_function(
            v8::Local<v8::Function> function,
            ext::vector<v8::Local<v8::Value>> arguments)
            -> void;

    auto create_host_function(
            v8::Local<v8::Function> function,
            v8::Local<v8::FunctionTemplate> type)
            -> v8::Function;

    auto wasm_to_js_value(
            v8::Local<v8::Value> wasm_value)
            -> v8::Value;

    template <typename T>
    auto js_to_wasm_value(
            v8::Local<v8::Value> js_value)
            -> v8::Value;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_EXPORTED_FUNCTIONS_INTERNALS_HPP
