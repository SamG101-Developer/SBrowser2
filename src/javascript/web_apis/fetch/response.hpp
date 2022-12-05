#pragma once
#ifndef SBROWSER2_RESPONSE_HPP
#define SBROWSER2_RESPONSE_HPP


#include "mixins/body.hpp"
namespace fetch {class response;}
namespace fetch {class response_private;}

#include INCLUDE_INNER_TYPES(fetch)
namespace fetch {class headers;}


class fetch::response
        : virtual public dom_object
        , public mixins::body
{
public constructors:
    response(detail::body_init_t&& body = nullptr, detail::response_init_t&& init = {});
    MAKE_PIMPL(response);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);

public js_methods:
    static auto error() -> std::unique_ptr<response>;
    static auto redirect(ext::string_view url, ext::number<ushort> status = 302) -> std::unique_ptr<response>;
    static auto json(const ext::any& data, ext::map<ext::string, ext::any>&& init = {}) -> std::unique_ptr<response>;

    auto clone() -> std::unique_ptr<response>;

private js_properties:
    DEFINE_GETTER(type, detail::response_type_t);
    DEFINE_GETTER(url, ext::string);
    DEFINE_GETTER(redirected, ext::boolean);
    DEFINE_GETTER(status, ext::number<ushort>);
    DEFINE_GETTER(ok, ext::boolean);
    DEFINE_GETTER(status_text, ext::u8string_view);
    DEFINE_GETTER(headers, headers*);
};


#endif //SBROWSER2_RESPONSE_HPP
