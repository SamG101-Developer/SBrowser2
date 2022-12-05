#include "fetch_internals.hpp"

#include "header_internals.hpp"


#include "fetch/_typedefs.hpp"
#include "fetch/detail/general_internals.hpp"
#include "fetch/detail/request_internals.hpp"
#include "fetch/detail/response_internals.hpp"

#include "html/_typedefs.hpp"
#include "html/detail/origin_internals.hpp"
#include "html/detail/policy_internals.hpp"
#include "html/detail/task_internals.hpp"

#include "referrer_policy/_typedefs.hpp"
#include "webappsec_cowl/detail/algorithm_internals.hpp"
#include "webappsec_csp/detail/integration_internals.hpp"
#include "webappsec_mixed_content/detail/algorithm_internals.hpp"
#include "dom/nodes/window.hpp"
#include "hr_time/detail/time_internals.hpp"
#include "url/detail/url_internals.hpp"


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

    auto e = js::env::env::from_global_object(request.client);
    auto task_destination = ext::variant<v8::Local<v8::Object>, html::detail::task_queue_t>{};
    auto cross_origin_isolated_capability = js::env::env::from_global_object(request.client).cpp.settings()->cross_origin_isolated_capability;

    if (!request.client.IsEmpty())
    {
        task_destination = e.js.global();
        cross_origin_isolated_capability = e.cpp.settings()->cross_origin_isolated_capability;
    }

    if (use_parallel_queue)
        task_destination = start_new_parallel_queue();

    auto timing_info = std::make_unique<fetch_timing_info_t>();
    timing_info->start_time = hr_time::detail::coarsen_shared_current_time(cross_origin_isolated_capability);
    timing_info->post_redirect_start_time = hr_time::detail::coarsen_shared_current_time(cross_origin_isolated_capability);;
    timing_info->render_blocking = request.render_blocking;

    auto fetch_params = std::make_unique<fetch_params_t>();
    fetch_params->request = &request;
    fetch_params->timing_info = std::move(timing_info);
    fetch_params->process_request_body_chunk_length = std::move(process_request_body_chunk_length);
    fetch_params->process_request_end_of_body = std::move(process_request_end_of_body);
    fetch_params->process_early_hints_response = std::move(process_early_hints_response);
    fetch_params->process_response = std::move(process_response);
    fetch_params->process_response_end_of_body = std::move(process_response_end_of_body);
    fetch_params->task_destination = std::move(task_destination);
    fetch_params->cross_origin_isolated_capability = cross_origin_isolated_capability;

    if (ext::holds_alternative<ext::u8string>(request.body))
        request.body = as_body(request.body);

    if (ext::get_and_equals<deferred_window_t>(request.window, deferred_window_t::CLIENT))
        request.window = e.cpp.global<dom::nodes::window*>() ? e.js.global() : deferred_window_t::NO_WINDOW;

    if (request.origin == u"client")
        request.origin = *e.cpp.settings()->origin;

    if (is_http_scheme(request.url->scheme)
            && ext::cmp::eq(request.mode, mode_t::SAME_ORIGIN, mode_t::CORS, mode_t::NO_CORS)
            && ext::get_and_equals<v8::Local<v8::Object>>(request.window, &v8::Local<v8::Object>::IsEmpty)
            && request.method == u"GET"
            && (!request.unsafe_request_flag || request.header_list.empty()))
    {
        ASSERT (
                html::detail::same_origin(request.origin, e.cpp.settings()->origin),
                "Request's origin must match the request's client's origin");

        auto on_preloaded_response_available =
                [fetch_params = *fetch_params](std::unique_ptr<response_t>&& response)
                {fetch_params->preloaded_response_candidate = std::move(response);};

        auto found_preloaded_resource = html::detail::consume_preloaded_resource(
                request.window, *request.url, request.destination, request.mode, request.credentials_mode,
                request.integrity_metadata, std::move(on_preloaded_response_available));

        if (found_preloaded_resource && ext::get_and_equals<response_t*>(fetch_params->preloaded_response_candidate, nullptr))
            fetch_params->preloaded_response_candidate = preload_response_t::PENDING;
    }

    if (ext::get_and_equals<policy_container_t>(request.policy_container, policy_container_t::CLIENT))
        request.policy_container = !request.client.IsEmpty()
            ? html::detail::clone_policy_container(ext::get<html::detail::policy_container_t*>(request.policy_container))
            : std::make_shared<html::detail::policy_container_t>();

    if (!header_list_contains_header(u8"Accept", request.header_list))
    {
        auto value = u"*/*";
        switch (request.destination)
        {
            case (destination_t::DOCUMENT):
            case (destination_t::FRAME):
            case (destination_t::IFRAME):
                value = u"text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8";
                break;

            case (destination_t::IMAGE):
                value = u"image/png,image/svg+xml,image/*;q=0.8,*/*;q=0.5";
                break;

            case (destination_t::STYLE):
                value = u"text/css,*/*;q=0.1";
                break;

            default:
                break;
        }

        append_header(header_t{u"Accept", std::move(value)}, request.header_list);
    }

    if (!header_list_contains_header(request.header_list, u"Accept-Language"))
        append_header(header_t{u"Accept-Language", u"en-GB"}, request.header_list); // TODO : choose appropriate value

    if (!request.priority.has_value())
        ; // TODO : algorthm for determining value, and set to proper type (enum?)

    if (is_subresource_request(request))
    {
        auto record = std::make_unique<fetch_record_t>();
        record->request = &request;
        record->controller = fetch_params->controller.get();
        e.cpp.settings()->fetch_group->fetch_records.emplace(std::move(record));
    }

    main_fetch(*fetch_params);
    return fetch_params->controller;
}


auto fetch::detail::main_fetch(
        fetch::detail::fetch_params_t& fetch_params,
        ext::boolean recursive)
        -> std::unique_ptr<response_t> // TODO : Mark off-spec code as off-spec: 'ARROW [SPEC] ARROW'
{
    // Set the 'request' to the request attatched to the 'fetch_params' parameter. The 'response' is a network error if
    // the only local urls are allowed by the request, and the request's current url isn't a local url. Otherwise,
    // default the response to a new response (unique_ptr).
    decltype(auto) request = *fetch_params.request;
    auto response = request.local_urls_only_flag && !is_local_url(request.current_url())
            ? create_appropriate_network_error(fetch_params)
            : std::make_unique<response_t>();

    // Report any content security policy violations from the request, and upgrade the request to a potentially
    // trustworthy url. All handled by webappsec-relate modules.
    webappsec::detail::report_content_security_policy_violations(request);
    webappsec::detail::upgrade_mixed_content_request_to_potentially_trustworthy_url_if_appropriate(request);

    // If there is any reason to blockthe request (for using a bad port, webappsec mixed content reasons or webappsec
    // content security policy reasons), then set the response to a return error (don't return yet as other attributes
    // might need adjusting still).
    if (should_request_be_blocked_due_to_bad_port(request)
            || webappsec::detail::should_request_be_blocked_as_cowl(request)
            || webappsec::detail::should_request_be_blocked_as_mixed_content(request)
            || webappsec::detail::should_request_be_blocked_by_content_security_policy(request))
        response.reset(create_appropriate_network_error(fetch_params));

    // If the request's referrer policy is empty, then set it to the request's policy container's referrer policy - the
    // policy container can be either an enum or object value; it has to be the object value here.
    if (request.referrer_policy == referrer_policy::detail::referrer_policy_t::_)
        request.referrer_policy = ext::get<1>(request.policy_container)->referrer_policy;

    // If the request's referrer is "no-referrer", then set it to the determined requests referrer (webappsec module)
    if (ext::get<0>(request.referrer) == referrer_t::NO_REFERRER)
        request.referrer = webappsec::detail::determine_requests_referrer(request);

    if (request.current_url().scheme == u"http"
            && url::detail::is_domain(request.current_url().scheme)
            /* TODO : && ... ??? */)
        request.current_url().scheme = u"https";

    auto request_handler =
            [recursive, &fetch_params, &request] -> std::unique_ptr<response_t>
            {

        // TODO : webappsec::detail::should_response_to_request_be_blocked_by_content_security_policy()?

        if (ext::get<1>(fetch_params.preloaded_response_candidate))
        {
            while (ext::holds_alternative<preload_response_t>(fetch_params.preloaded_response_candidate)) continue;
            ASSERT (ext::get<1>(fetch_params.preloaded_response_candidate));
            ext::unsafe_get<1>(fetch_params.preloaded_response_candidate);
        }

        if (html::detail::same_origin(url::detail::origin(request.current_url()), request.origin) && request.response_tainting == response_tainting_t::BASIC
                || request.current_url().scheme == u"data"
                || request.mode == mode_t::NAVIGATE || request.mode == mode_t::WEBSOCKET)
        {
            request.response_tainting = response_tainting_t::BASIC;
            return scheme_fetch(fetch_params);
        }

        if (request.mode == mode_t::NAVIGATE || request.mode == mode_t::WEBSOCKET)
            return create_appropriate_network_error(fetch_params);

        if (request.mode == mode_t::NO_CORS)
            return_if (request.redirect_mode != redirect_t::FOLLOW) create_appropriate_network_error(fetch_params);
            request.response_tainting = response_tainting_t::OPAQUE;
            return scheme_fetch(fetch_params);

        if (!is_https_scheme(request.current_url().scheme))
            return create_appropriate_network_error(fetch_params);

        if (request.use_cors_preflight_flag
                || request.unsafe_request_flag && (!is_cors_safelisted_method(request.method) || !is_cors_unsafe_request_header_names(request.header_list).empty()))
        {
            request.response_tainting = response_tainting_t::CORS;
            auto cors_with_preflight_response = http_fetch(fetch_params, true);
            if (is_network_error(*cors_with_preflight_response)) clear_cache_entries(request);
            return cors_with_preflight_response;
        }

        if (recursive)
            return response;

        if (!is_network_error(*response) && !is_filtered_response(*response))
            ; // TODO

        if (webappsec::detail::process_response_to_request_as_cowl(request, response))
            response.reset(create_appropriate_network_error(fetch_params));
            };

    if (!recursive)
        GO request_handler;
    else
        request_handler();
}
