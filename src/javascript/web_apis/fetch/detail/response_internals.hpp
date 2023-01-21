#ifndef SBROWSER2_RESPONSE_INTERNALS_HPP
#define SBROWSER2_RESPONSE_INTERNALS_HPP

#include <memory>


#include "ext/expected.ixx"

#include "ext/vector.hpp"

#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(url)
#include INCLUDE_INNER_TYPES(service_workers)

namespace fetch {class response;}


namespace fetch::detail
{










    auto create_response_object(
            std::unique_ptr<response_t>&& inner_response,
            header_guard_t header_guard)
            -> std::unique_ptr<response>;

    auto initialize_response_object(
            response* response_object,
            response_init_t&& init,
            body_with_type_t&& body = nullptr)
            -> void;
}




#endif //SBROWSER2_RESPONSE_INTERNALS_HPP
