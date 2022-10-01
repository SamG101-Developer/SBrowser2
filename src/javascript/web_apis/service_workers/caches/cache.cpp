#include "cache.hpp"

#include "ext/promise.hpp"


auto service_workers::caches::cache::match(
        fetch::detail::request_info_t request,
        detail::cache_query_options_t&& options)
        -> ext::promise<fetch::response*>
{
    auto promise = ext::promise<fetch::response*>{};
    GO [this, &promise, &request, options = std::move(options)] mutable
    {
        auto match_all_promise = match_all(request, std::move(options));
        match_all_promise.wait_to_settle();
        // TODO
    };

    return promise;
}
