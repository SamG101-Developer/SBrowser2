#include "request_internals.hpp"

#include "ext/casting.hpp"
#include "ext/enums.hpp"

#include "fetch/_typedefs.hpp"
#include "url/detail/url_internals.hpp"


auto fetch::detail::is_subresource_request(const fetch::detail::request_t& request) -> ext::boolean
{
    return request.destination & (destination_t::AUDIO | destination_t::AUDIOWORKLET | destination_t::FONT
            | destination_t::IMAGE | destination_t::MANIFEST | destination_t::PAINTWORKLET | destination_t::SCRIPT
            | destination_t::STYLE | destination_t::TRACK | destination_t::VIDEO | destination_t::XSLT
            | destination_t::_);
}


auto fetch::detail::is_non_subresource_request(const fetch::detail::request_t& request) -> ext::boolean
{
    return request.destination & (destination_t::DOCUMENT | destination_t::EMBED | destination_t::FRAME
            | destination_t::IFRAME | destination_t::OBJECT | destination_t::REPORT | destination_t::SERVICEWORKER
            | destination_t::SHAREDWORKER | destination_t::WORKER);
}


auto fetch::detail::is_navigation_request(const fetch::detail::request_t& request) -> ext::boolean
{
    return request.destination & (destination_t::DOCUMENT | destination_t::EMBED | destination_t::FRAME
            | destination_t::IFRAME | destination_t::OBJECT);
}


auto fetch::detail::has_redirect_tainted_origin(const fetch::detail::request_t& request) -> ext::boolean
{
    decltype(auto) last_url = ext::nullptr_cast<url::detail::url_t*>();
    for (decltype(auto) current_url: request.url_list) // TODO : find nicer way with ranges-v3
    {
        if (!last_url)
            last_url = current_url;
        else
        {
            return_if (!url::detail::same_origin(url::detail::origin(*current_url), url::detail::origin(*last_url))
                    && !url::detail::same_origin(request->origin, url::detail::origin(*last_url))) true;
            last_url = current_url;
        }
    }

    return false;
}
