#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_GLOBAL_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_GLOBAL_INTERNALS_HPP


#include <v8-forward.h>
#include <v8-platform.h>
namespace web_assembly::js {class global;}


namespace web_assembly::detail
{
    auto initialize_global_object(
            v8::Local<v8::VirtualAddressSpace> global_address)
            -> void;

    auto create_global_object(
            v8::Local<v8::VirtualAddressSpace> global_address)
            -> js::global;

    auto to_value_types(
            ext::string_view string)
            -> v8::Local<v8::Value>;

    template <typename T_V8, typename T>
    auto default_value()
            -> T;

    auto get_global_value(
            js::global* global)
            -> v8::Local<v8::Value>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_GLOBAL_INTERNALS_HPP
