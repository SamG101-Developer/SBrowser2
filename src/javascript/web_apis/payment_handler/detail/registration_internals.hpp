#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_DETAIL_REGISTRATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_DETAIL_REGISTRATION_INTERNALS_HPP

#include "ext/vector.hpp"
#include USE_INNER_TYPES(payment_handler)


namespace payment::detail
{
    auto is_valid_sizes(
            ext::string_view sizes)
            -> ext::boolean;

    auto convert_image_object(
            ext::vector_view<detail::image_object_t*> input_images)
            -> ext::vector<detail::image_object_t*>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_DETAIL_REGISTRATION_INTERNALS_HPP
