#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_INSTRUMENTS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_INSTRUMENTS_HPP

#include "ext/map_like.hpp"
namespace payment::handler {class payment_instruments;}

#include "ext/promise.hpp"
#include INCLUDE_INNER_TYPES(payment_handler)

#include "payment_instruments_private.hpp"


class payment::handler::payment_instruments
        : public ext::map_like_linked<ext::string, detail::payment_instrument_t>
{
public constructors:
    payment_instruments();
    MAKE_PIMPL(payment_instruments);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto delete_(ext::string_view instrument_key) -> ext::promise<ext::boolean>;
    auto get(ext::string_view instrument_key) const -> ext::promise<ext::any>;
    auto keys() const -> ext::vector<ext::string>;
    auto has(ext::string_view instrument_key) const -> ext::promise<ext::boolean>;
    auto set(ext::string_view instrument_key, detail::payment_instrument_t&& details) -> ext::promise<void>;
    auto clear() -> ext::promise<void>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_INSTRUMENTS_HPP
