#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CLIENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CLIENT_HPP

#include "dom_object.hpp"
namespace service_workers::clients {class client;}
namespace service_workers::clients {class client_private;}

#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(service_workers)


class service_workers::clients::client
        : public virtual dom_object
{
public constructors:
    client();
    MAKE_PIMPL(client);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto post_message(ext::any&& message, ext::vector<ext::any>&& transfer) -> void;
    auto post_message(ext::any&& message, html::detail::structured_serialize_options_t&& options = {}) -> void;

private js_properties:
    DEFINE_GETTER(url, ext::string);
    DEFINE_GETTER(id, ext::string);
    DEFINE_GETTER(frame_type, detail::frame_type_t);
    DEFINE_GETTER(client_type, detail::frame_type_t);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_DETAIL_CLIENT_HPP
