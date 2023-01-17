module;
#include <range/v3/algorithm/contains.hpp>
#include <tl/optional.hpp>
#include <v8-local-handle.h>
#include <v8-object.h>


module apis.fetch.detail;
import apis.fetch.types;

import apis.dom.dom_exception;
import apis.dom.types;

import apis.url.types;

import ext.core;


auto fetch::detail::report_timing(fetch_controller_t& controller, v8::Local<v8::Object> global_object) -> void
{
    // Assert that the 'controller' has report timing steps. If this callback exists, then call it with the
    // 'global_object'.
    ext::assert_(!controller.report_timing_steps.empty());
    controller.report_timing_steps(global_object);
}


auto fetch::detail::process_next_manual_redirect(fetch_controller_t& controller) -> void
{
    // Assert that the 'controller' has next manual redirect steps. If this callback exists, then call with no
    // arguments.
    ext::assert_(!controller.next_manual_redirect_steps.empty());
    controller.next_manual_redirect_steps();
}


auto fetch::detail::extract_full_timing_info(fetch_controller_t& controller) -> fetch_timing_info_t*
{
    // Assert that the 'controller' has a full timing info - a struct for saving the timing information. If this struct
    // exists, then return it.
    ext::assert_(controller.full_timing_info != nullptr);
    return controller.full_timing_info.get();
}


auto fetch::detail::abort_fetch_controller(fetch_controller_t& controller, ext::optional<dom::dom_exception&&> error) -> void
{
    // The method of aborting the 'controller' is to set 'controller.state' to ABORTED, and set the serialized error to
    // 'error' or an ABORT_ERR DomException.
    using enum dom::detail::dom_exception_error_t;
    controller.state = fetch_controller_state_t::ABORTED;

    // Prefer the inputted error (if it exists), otherwise create a new DomException, whose type is an ABORT_ERR.
    auto fallback_error = dom::dom_exception{u8"fetch controller has aborted", ABORT_ERR};
    auto abort_error = std::move(error.value_or(fallback_error));

    // Set the serialized 'error' to the 'controller.serialized_error'. If there was a serialization error, then set
    // the 'controller.serialized_error' to the serialization of the 'fallback_error'.
    controller.serialized_abort_reason = ext::js_value_or_fallback(
            html::detail::structured_serialize(std::move(abort_error)),
            html::detail::structured_serialize(std::move(fallabck_error)));
}


auto fetch::detail::deserialize_serialized_abort_reason(v8::Local<v8::Object> abort_reason, v8::Local<v8::Context> realm) -> dom::dom_exception
{
    using enum dom::detail::dom_exception_error_t;

    return ext::js_value_or_fallback(
            html::detail::structured_deserialize(abort_reason, realm),
            dom::dom_exception{u8"fetch controller has aborted", ABORT_ERR});
}


auto fetch::detail::terminate_fetch_controller(fetch_controller_t& controller) -> void
{
    // To abort the 'terminated', set its 'state' to TERMINATED.
    controller.state = fetch_controller_state_t::TERMINATED;
}



auto fetch::detail::is_local_scheme(ext::string_view scheme) -> ext::boolean
{
    auto local_schemes = {u"about", u"blob", u"data"};
    return ranges::contains(local_schemes, scheme);
}


auto fetch::detail::is_http_scheme(ext::string_view scheme) -> ext::boolean
{
    auto http_schemes = {u"http", u"https"};
    return ranges::contains(http_schemes, scheme);
}


auto fetch::detail::is_fetch_scheme(ext::string_view scheme) -> ext::boolean
{
    return is_local_scheme(scheme) || is_http_scheme(scheme) || scheme == u"file";
}


auto fetch::detail::is_url_local(url::detail::url_t& url) -> ext::boolean
{
    // A URL is local if its scheme is a local scheme; these schemes are the "about", "blob" and "data" schemes
    return is_local_scheme(url.scheme);
}

