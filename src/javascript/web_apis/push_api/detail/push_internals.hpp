#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_DETAIL_PUSH_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_DETAIL_PUSH_INTERNALS_HPP

#include "ext/keywords.ixx"
#include INCLUDE_INNER_TYPES(push_api)
#include INCLUDE_INNER_TYPES(web_idl)
namespace push_api {class push_message_data;}
namespace push_api {class push_subscription;}


namespace push_api::detail
{
    auto create_push_subscription(
            push_subscription_options_init_t&& options)
            -> push_subscription;

    auto refresh(
            push_subscription* subscription)
            -> void;

    auto deactivate(
            push_subscription* subscription)
            -> void;

    auto extract_byte_sequence(
            ext::variant<ext::string_view, v8::Local<v8::BufferSource>> object)
            -> ext::string;

    auto on_receive_push_message(
            push_message_data* message)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_DETAIL_PUSH_INTERNALS_HPP
