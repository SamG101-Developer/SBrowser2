#ifndef SBROWSER2_EXTENSION_INTERNALS_HPP
#define SBROWSER2_EXTENSION_INTERNALS_HPP




#include <v8-object.h>

#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(html)


namespace fetch::detail
{



    auto is_cors_request_response(
            response_t& response_object)
            -> ext::boolean;

    auto is_cors_preflight_request_response(
            response_t& response_object)
            -> ext::boolean;

    auto is_cors_non_preflight_request_response(
            response_t& response_object)
            -> ext::boolean;
}


#endif //SBROWSER2_EXTENSION_INTERNALS_HPP
