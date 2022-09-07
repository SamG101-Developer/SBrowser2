#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_INSTRUMENTS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_INSTRUMENTS_HPP

#include "dom_object.hpp"
#include "ext/map_like.hpp"
namespace payment::handler {class payment_instruments;}

#include USE_INNER_TYPES(payment_handler)


class payment::handler::payment_instruments
        : public dom_object
        , public ext::map_like_linked<ext::string, detail::payment_instrument_t>
{
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_INSTRUMENTS_HPP
