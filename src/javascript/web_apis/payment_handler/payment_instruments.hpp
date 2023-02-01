#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_INSTRUMENTS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_INSTRUMENTS_HPP

#include "ext/map_like.ixx"
namespace payment::handler {class payment_instruments;}
namespace payment::handler {class payment_instruments_private;}


#include INCLUDE_INNER_TYPES(payment_handler)


class payment::handler::payment_instruments
        : public ext::map_like_linked<ext::string, detail::payment_instrument_t>
{
public constructors:
    payment_instruments();
    MAKE_PIMPL(payment_instruments);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto delete_(ext::string_view instrument_key) -> ext::promise<ext::boolean>;
    auto get(ext::string_view instrument_key) const -> ext::promise<ext::any>;
    auto keys() const -> ext::promise<ext::vector<ext::string>>;
    auto has(ext::string_view instrument_key) const -> ext::promise<ext::boolean>;
    auto set(ext::string_view instrument_key, detail::payment_instrument_t&& details) -> ext::promise<void>;
    auto clear() -> ext::promise<void>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_INSTRUMENTS_HPP
