#include "presentation_internals.hpp"
#include "presentation/presentation_request.hpp"

#include "ext/enums.hpp"
#include "ext/optional.hpp"
#include "javascript/environment/environment_settings.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(html)

#include "dom/detail/exception_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_private.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "html/detail/sandboxing_internals.hpp"
#include "url/detail/url_internals.hpp"

#include <range/v3/view/filter.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/transform.hpp>


auto presentation::detail::construct_presentation_request(
        presentation::presentation_request* request,
        ext::vector_span<ext::string> urls)
        -> presentation_request*
{
    using enum dom::detail::dom_exception_error_t;

    JS_REALM_GET_RELEVANT(request);
    decltype(auto) document = v8pp::from_v8<dom::nodes::window*>(request_relevant_agent, request_relevant_global_object)->d_func()->document;
    decltype(auto) api_base_url = *v8pp::from_v8<javascript::environment::settings_t*>(current_agent, current_settings_object)->api_base_url;

    dom::detail::throw_v8_exception_formatted<SECURITY_ERR>(
            [document] {return document->d_func()->active_sandboxing_set & html::detail::sandboxing_flag_set_t::PRESENTATION;},
            u8"Document flag disallows presentations being used");

    decltype(auto) presentation_urls = urls
            | ranges::views::transform(BIND_BACK(url::detail::basic_url_parser, api_base_url))
            | ranges::views::for_each([](auto&& url) {dom::detail::throw_v8_exception_formatted<SYNTAX_ERR>([&url] {return !url.has_value();}, u8"URL Parsing Error");});
    // TODO : filter by allowed schemes

    dom::detail::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
            [&presentation_urls] {return presentation_urls.empty();},
            u8"Must have > 0 URLS");

    return request;
}