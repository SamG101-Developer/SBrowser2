#ifndef SBROWSER2_REQUEST_INTERNALS_HPP
#define SBROWSER2_REQUEST_INTERNALS_HPP




#include "fetch/_typedefs.hpp"

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(referrer_policy)
#include INCLUDE_INNER_TYPES(url)

namespace fetch {class headers;}
namespace fetch {class request;}
namespace js::env {class env;}


namespace fetch::detail
{
    auto create_request_object(
            std::unique_ptr<request_t>&& inner_request,
            header_guard_t header_guard)
            -> std::unique_ptr<request>;
}




#endif //SBROWSER2_REQUEST_INTERNALS_HPP
