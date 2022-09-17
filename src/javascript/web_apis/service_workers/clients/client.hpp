#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CLIENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CLIENT_HPP

#include "dom_object.hpp"
namespace service_workers::clients {class client;}

#include "ext/vector.hpp"
#include USE_INNER_TYPES(service_workers)


class service_workers::clients::client
{
public constructors:
    DOM_CTORS(client);
    client() = default;

public js_methods:
    auto post_message(const ext::any& message, const ext::vector<ext::any>& transfer) -> void;
    auto post_message(const ext::any& message, html::detail::structure_serialize_options_t&& options = {}) -> void;

public js_methods:
    ext::property<ext::string> url;
    ext::property<ext::string> id;
    ext::property<detail::frame_type_t> frame_type;
    ext::property<detail::frame_type_t> client_type;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(url);
    DEFINE_CUSTOM_GETTER(id);
    DEFINE_CUSTOM_GETTER(frame_type);
    DEFINE_CUSTOM_GETTER(client_type);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CLIENT_HPP
