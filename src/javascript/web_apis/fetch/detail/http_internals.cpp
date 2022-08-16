#include "http_internals.hpp"

#include <initializer_list>
#include "ext/ranges.hpp"
#include "url/url.hpp"

#include <range/v3/algorithm/contains.hpp>


auto fetch::detail::report_timing(
        fetch_controller_t* controller,
        v8::Local<v8::Object> global_object)
        -> void
{
    // assert that the 'controller' has report timing steps - a callback for reporting the timing information; if this
    // callback exists, then call it with the 'global_object'
    assert(controller->report_timing_steps.has_value());
    controller->report_timing_steps.value()(global_object);
}


auto fetch::detail::extract_full_timing_info(
        fetch_controller_t* controller)
        -> fetch_timing_info_t*
{
    // assert that the 'controller' has a full timing info - a struct for saving the timing information; if this struct
    // exists, then return it
    assert(controller->full_timing_info);
    return controller->full_timing_info;
}


auto fetch::detail::abort_fetch_controller(
        fetch_controller_t* controller)
        -> void
{
    // to abort the 'controller', set its 'state' to the ABORTED state
    controller->state = fetch_controller_state_t::ABORTED;
}


auto fetch::detail::terminate_fetch_controller(
        fetch_controller_t* controller)
        -> void
{
    // to abort the 'terminated', set its 'state' to the TERMINATED state
    controller->state = fetch_controller_state_t::TERMINATED;
}


auto fetch::detail::is_aborted(
        fetch_controller_t* controller)
        -> ext::boolean
{
    // a 'controller' is aborted if its 'state' is ABORTED
    return controller->state == fetch_controller_state_t::ABORTED;
}


auto fetch::detail::is_cancelled(
        fetch_controller_t* controller)
        -> ext::boolean
{
    // a 'controller' is cancelled if its 'state' is ABORTED or TERMINATED
    return controller->state == fetch_controller_state_t::ABORTED || controller->state == fetch_controller_state_t::TERMINATED;
}


auto fetch::detail::is_url_local(
        url::url_object& url)
        -> ext::boolean
{
    // a url is local if its scheme is a local scheme; these schemes are the "about", "blob" and "data" schemes
    ext::string url_local_schemes[3] {"about", "blob", "data"};
    return ranges::contains(url_local_schemes, url.scheme());
}


auto fetch::detail::is_cors_safelisted_method(
        ext::string_view method)
        -> ext::boolean
{
    ext::string cors_safelisted_methods[3] {"GET", "HEAD", "POST"};
    return ranges::contains(cors_safelisted_methods, normalize_method(method));
}


auto fetch::detail::is_forbidden_method(
        ext::string_view method)
        -> ext::boolean
{
    ext::string forbidden_methods[3] {"CONNECT", "TRACE", "TRACK"};
    return ranges::contains(forbidden_methods, normalize_method(method));
}


auto fetch::detail::normalize_method(
        ext::string_view method)
        -> ext::string
{
    return method | ranges::views::uppercase() | ranges::to<ext::string>();
}
