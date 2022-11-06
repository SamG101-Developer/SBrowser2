#include "cache.hpp"
#include "cache_private.hpp"

#include "ext/promise.hpp"
#include "ext/ranges.hpp"

#include "javascript/environment/realms.hpp"

#include INCLUDE_INNER_TYPES(fetch)

#include "dom/detail/observer_internals.hpp"
#include "fetch/request.hpp"
#include "fetch/response.hpp"
#include "fetch/detail/extension_internals.hpp"
#include "service_workers/detail/cache_internals.hpp"

#include <range/v3/view/for_each.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/take.hpp>
#include <v8-exception.h>


auto service_workers::caches::cache::match(
        fetch::detail::request_info_t&& request,
        detail::cache_query_options_t&& options)
        -> ext::promise<fetch::response*>
{
    auto promise = ext::promise<fetch::response*>{};
    GO [this, &promise, &request, options = std::move(options)] mutable
    {
        auto match_all_promise = match_all(std::move(request), std::move(options));
        match_all_promise.wait_to_settle();
        // TODO
    };

    return promise;
}


auto service_workers::caches::cache::match_all(
        ext::optional<fetch::detail::request_info_t> request,
        detail::cache_query_options_t&& options)
        -> ext::promise<ext::vector_span<fetch::response*>>
{
    ACCESS_PIMPL(cache);
    auto promise = ext::promise<ext::vector_span<fetch::response*>>{};

    decltype(auto) r = ext::nullptr_cast<fetch::request*>();
    if (request.has_value() && ext::holds_alternative<fetch::request*>(*request))
    {
        r = ext::get<fetch::request*>(std::move(*request));
        return_if (r.d_func()->method != fetch::detail::method_t::GET && !options.try_emplace("ignoreMethod").first()->second.to<ext::boolean>()) promise.resolve({});
    }
    else if (request.has_value() && ext::holds_alternative<ext::string>(*request))
    {
        JS_EXCEPTION_HANDLER;
        r = std::make_unique<fetch::request>(std::move(ext::get<ext::string>(std::move(*request)))).get();
        return_if (JS_EXCEPTION_HAS_THROWN) promise.reject(JS_EXCEPTION);
    }

    GO [d, r, &promise, &request, options = std::move(options)] mutable
    {
        auto responses = request.has_value()
                ? *d->request_response_list | ranges::views::values
                : detail::query_cache(r, std::move(options)) | ranges::views::values;

        auto reject_cross_origin = [&promise](fetch::response* response)
        {
            auto e = js::env::env::relevant(promise);
            return response->d_func()->type == u8"opaque" && !fetch::detail::cross_origin_resource_policy_checl(e.cpp.settings()->origin, e.js.global(), u8"", response);
        };

        responses
                | ranges::views::filter(std::move(reject_cross_origin))
                | ranges::views::take(1)
                | ranges::views::for_each(BIND_FRONT(&promise.reject, v8::Exception::TypeError()));

        dom::detail::queue_task(/* TODO */);
    };

    return promise;
}


auto service_workers::caches::cache::add(
        fetch::detail::request_info_t&& request)
        -> ext::promise<void>
{
    decltype(auto) response_array_promise = add_all({std::move(request)});
    return response_array_promise.react([] {});
}
