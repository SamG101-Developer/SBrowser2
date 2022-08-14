#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_DETAIL_ECMA_BINDING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_DETAIL_ECMA_BINDING_INTERNALS_HPP

#include "indexed_db/_typedefs.hpp"
#include <v8-forward.h>


namespace indexed_db::detail::ecma_binding_internals
{
    auto extract_key_from_value_using_key_path(
            const ext::any& value,
            const key_path_t& key_path,
            const ext::boolean& multi_entry_flag)
            -> record_t;

    auto evaluate_key_path_on_value(
            const ext::any& value,
            const key_path_t& key_path)
            -> v8::Local<v8::Object>;

    auto check_key_can_be_injected_into_value(
            const ext::any& value,
            const any_key_t& key,
            const key_path_t& key_path)
            -> void;

    auto convert_key_to_value(
            const any_key_t& key)
            -> ext::any;

    auto convert_value_to_key(
            const ext::any key)
            -> any_key_t;

    auto convert_value_to_multi_entry_key(
            const ext::any key)
            -> any_key_t;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INDEXED_DB_DETAIL_ECMA_BINDING_INTERNALS_HPP
