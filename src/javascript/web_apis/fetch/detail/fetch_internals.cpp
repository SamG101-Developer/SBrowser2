#include "fetch_internals.hpp"

#include "javascript/environment/realms.hpp"

#include "fetch/_typedefs.hpp"
#include "fetch/detail/request_internals.hpp"
#include "fetch/detail/response_internals.hpp"

#include "html/_typedefs.hpp"
#include "html/detail/task_internals.hpp"


auto fetch::detail::fetch(
        fetch::detail::request_t& request,
        ext::function<void(ext::number<int>)>&& process_request_body_chunk_length,
        ext::function<void()>&& process_request_end_of_body,
        ext::function<void(response_t&)>&& process_early_hints_response,
        ext::function<void(response_t&)>&& process_response,
        ext::function<void(response_t&)>&& process_response_end_of_body,
        ext::function<void(response_t&, ext::string_view)>&& process_response_consume_body,
        ext::boolean use_parallel_queue)
        -> std::unique_ptr<response_t>
{
    assert (request.mode == mode_t::NAVIGATE || process_early_hints_response.empty());

    auto task_destination = html::detail::task_queue_t{};
    auto cross_origin_isolated_queue = js::env::env::from_global_object(request.client).cpp.settings()->cross_origin_isolated_capability;
}
