#pragma once
#ifndef SBROWSER2_RESPONSE_HPP
#define SBROWSER2_RESPONSE_HPP

#include "mixins/body.hpp"
namespace fetch {class response;}

#include USE_INNER_TYPES(fetch)


class fetch::response
        : public mixins::body
{
public constructors:
    response();

public js_methods:
    auto error() -> response;
    auto redirect(ext::string_view url, const ext::number<ushort>& status = 302);
    auto json(const ext::any& data, ext::map<ext::string, ext::any>&& init = {});

    auto clone() -> response;

public js_properties:
    ext::property<ext::string> type; // TODO : constrain property value
    ext::property<ext::string> url;
    ext::property<ext::boolean> redirected;
    ext::property<ext::number<ushort>> status;
    ext::property<ext::boolean> ok;
    ext::property<ext::string> status_text;
    ext::property<detail::headers_t> headers;
};


#endif //SBROWSER2_RESPONSE_HPP
