#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_MEMORY_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_MEMORY_INTERNALS_HPP

#include <v8-forward.h>
namespace web_assembly::js {class memory;}


namespace web_assembly::detail
{
    auto create_memory_buffer(
            v8::Local<v8::WasmMemoryObject> memory_address)
            -> v8::ArrayBuffer;

    auto initialize_memory_object(
            js::memory* memory,
            v8::Local<v8::WasmMemoryObject> memory_address)
            -> void;

    auto create_memory_object(
            v8::Local<v8::WasmMemoryObject> memory_address)
            -> js::memory;

    auto reset_memory_buffer(
            v8::Local<v8::WasmMemoryObject> memory_address)
            -> v8::ArrayBuffer;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_MEMORY_INTERNALS_HPP
