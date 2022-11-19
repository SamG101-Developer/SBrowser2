#include "algorithm_internals.hpp"

#include "ext/ranges.hpp"
#include "html/_typedefs.hpp"
#include "javascript/environment/realms.hpp"

#include "dom/nodes/document.hpp"
#include "dom/nodes/document_private.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "fetch/detail/header_internals.hpp"
#include "fetch/detail/response_internals.hpp"

#include "html/detail/context_internals.hpp"
#include "html/detail/origin_internals.hpp"
#include "html/detail/sandboxing_internals.hpp"
#include "html/other/location.hpp"
#include "html/other/location_private.hpp"

#include "url/detail/url_internals.hpp"
#include "webappsec_mixed_content/detail/algorithm_internals.hpp"

#include <range/v3/algorithm/contains.hpp>


auto webappsec::detail::parse_response_clear_site_data_header(
        const fetch::detail::response_t& response)
        -> fetch::detail::header_values_t
{
    auto types = fetch::detail::header_values_t{};
    auto header_values = fetch::detail::extract_header_list_values(u"Clear-Site-Data", response.header_list);
    return_if (!header_values.has_value() || header_values->empty()) {};

    for (auto&& header_value: *header_values)
        types |= ranges::actions::multi_push_back(header_value == u"*" ? u"cache", u"cookies", u"sotrgae", u"executionContexts" : header_value);

    return types;
}


auto webappsec::detail::clear_site_data_for_response(
        const fetch::detail::response_t& response)
        -> void
{
    return_if (!is_prior_authenticated_url(response.url()));
    auto types = parse_response_clear_site_data_header(response);
    auto browsing_contexts = prepare_to_clear_origins_data(url::detail::origin(response.url()), types);
    auto origin = url::detail::origin(response.url());

    if (ranges::contains(types, u"cache"))
        clear_cache_for_origin(origin);

    if (ranges::contains(types, u"cookies"))
        clear_cookies_for_origin(origin);

    if (ranges::contains(types, u"storage"))
        clear_dom_accessible_storage_for_origin(origin);

    if (ranges::contains(types, u"executionContexts"))
        reload_browsing_contexts(browsing_contexts);
}


auto webappsec::detail::prepare_to_clear_origins_data(
        const html::detail::origin_t& origin,
        ext::vector_span<ext::string> types)
        -> ext::vector<html::detail::browsing_context_t*>
{
    return_if (!ranges::contains(types, u"executionContexts")) {};
    auto e = js::env::env::current(); // TODO : which environment?

    auto sandboxed = ext::vector<html::detail::browsing_context_t*>{};
    for (decltype(auto) context: e.cpp.settings()->browsing_contexts)
    {
        decltype(auto) document = html::detail::active_document(*context);
        continue_if (*js::env::env::relevant(document).cpp.settings()->origin != origin);
        html::detail::parse_sandboxing_directive(u"", &document->d_func()->active_sandboxing_set);
        sandboxed.emplace_back(context);
    }

    return sandboxed;
}


auto webappsec::detail::reload_browsing_contexts(
        ext::vector_span<html::detail::browsing_context_t*> context)
        -> void
{
    auto reloader = [](html::detail::browsing_context_t* context)
    {
        decltype(auto) active_document = html::detail::active_document(*context);
        decltype(auto) global_object = js::env::env::relevant(active_document).cpp.global<dom::nodes::window*>();
        global_object->d_func()->location->reload();
    };

    context | ranges::views::for_each(std::move(reloader));
}
