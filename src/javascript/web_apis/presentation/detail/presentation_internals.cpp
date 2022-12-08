#include "presentation_internals.hpp"
#include "presentation/presentation_request.hpp"

#include "ext/enums.ixx"
#include "ext/optional.ixx"



#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(html)







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

    auto e = js::env::env::current();
    decltype(auto) document = e.cpp.global<dom::nodes::window*>()->d_func()->document;
    decltype(auto) api_base_url = *e.cpp.settings()->api_base_url;

    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [document] {return document->d_func()->active_sandboxing_set & html::detail::sandboxing_flag_set_t::PRESENTATION;},
            u8"Document flag disallows presentations being used");

    decltype(auto) presentation_urls = urls
            | ranges::views::transform(BIND_BACK(url::detail::basic_url_parser, api_base_url))
            | ranges::views::for_each([](auto&& url) {dom::detail::throw_v8_exception<SYNTAX_ERR>([&url] {return !url.has_value();}, u8"URL Parsing Error");});
    // TODO : filter by allowed schemes

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [&presentation_urls] {return presentation_urls.empty();},
            u8"Must have > 0 URLS");

    return request;
}
