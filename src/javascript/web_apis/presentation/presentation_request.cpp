#include "presentation_request.hpp"
#include "presentation_request_private.hpp"

#include "presentation/detail/presentation_internals.hpp"


presentation::presentation_request::presentation_request(ext::string&& url)
        : presentation_request(ext::vector<ext::string>{std::move(url)})
{}


presentation::presentation_request::presentation_request(ext::vector_span<ext::string> urls)
{
    INIT_PIMPL(presentation_request);
    detail::construct_presentation_request(this, urls);
}


auto presentation::presentation_request::start()
        -> ext::promise<presentation_connection>
{
    return detail::select_presentation_display(this);
}


auto presentation::presentation_request::reconnect()
        -> ext::promise<presentation_connection>
{
    return detail::reconnect_to_presentation(this);
}
