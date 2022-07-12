#pragma once
#ifndef SBROWSER2_RESPONSE_HPP
#define SBROWSER2_RESPONSE_HPP

#include "mixins/body.hpp"
namespace fetch {class response;}

#include "_typedefs.hpp"


class fetch::response
        : public mixins::body
{
public constructors:
    response();

public js_methods:
    auto error() -> response;
    auto redirect(ext::string_view url, ext::number_view<ushort> status = 302);
    auto json(ext::any_view data, ext::string_any_map_view init = {});

    auto clone() -> response;

public js_properties:
    ext::property<ext::string> type; // TODO : constrain property value
    ext::property<ext::string> url;
    ext::property<ext::boolean> redirected;
    ext::property<ext::number<ushort>> status;
    ext::property<ext::boolean> ok;
    ext::property<ext::string> status_text;
    ext::property<headers_t> headers;
};


#endif //SBROWSER2_RESPONSE_HPP
