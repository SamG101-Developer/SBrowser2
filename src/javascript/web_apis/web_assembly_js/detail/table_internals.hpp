#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_TABLE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_TABLE_INTERNALS_HPP

#include <v8-forward.h>
#include <v8-platform.h>

namespace web_assembly::js {class table;}


namespace web_assembly::detail
{
    auto initialize_table_object(
            v8::Local<v8::VirtualAddressSpace> table_address)
            -> void;

    auto create_table_object(
            v8::Local<v8::VirtualAddressSpace> table_address)
            -> js::table;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_DETAIL_TABLE_INTERNALS_HPP
