#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_INSTRUMENTS_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_INSTRUMENTS_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "ext/map_like.ixx"

#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(payment_handler)


DEFINE_PRIVATE_CLASS(payment::handler, payment_instruments) : ext::map_like_linked_private<ext::string, payment::detail::payment_instrument_t>{};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_INSTRUMENTS_PRIVATE_HPP
