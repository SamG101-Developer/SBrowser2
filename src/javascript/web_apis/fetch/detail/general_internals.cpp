#include "general_internals.hpp"

#include "ext/ranges.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/other/dom_exception.hpp"

#include "fetch/detail/request_internals.hpp"
#include "html/detail/task_internals.hpp"

#include <initializer_list>
#include <range/v3/algorithm/contains.hpp>


fetch::detail::fetch_group_t::~fetch_group_t()
{
    using enum ranges::filter_compare_t;

    fetch_records
            | ranges::views::filter_eq<NE>(&fetch_record_t::controller, nullptr, ext::underlying)
            | ranges::views::filter([](fetch_record_t* record) {return !record->request->done_flag || !record->request->keep_alive;})
            | ranges::views::for_each([](fetch_record_t* record) {terminate_fetch_controller(*record->controller);});
}


auto fetch::detail::report_timing(
        fetch_controller_t& controller,
        v8::Local<v8::Object> global_object)
        -> void
{
    // assert that the 'controller' has report timing steps - a callback for reporting the timing information; if this
    // callback exists, then call it with the 'global_object'
    assert(!controller.report_timing_steps.empty());
    controller.report_timing_steps(global_object);
}


auto fetch::detail::process_next_manual_redirect(
        fetch_controller_t& controller)
        -> void
{
    assert(!controller.next_manual_redirect_steps.empty());
    controller.next_manual_redirect_steps();
}


auto fetch::detail::extract_full_timing_info(
        fetch_controller_t& controller)
        -> fetch_timing_info_t*
{
    // assert that the 'controller' has a full timing info - a struct for saving the timing information; if this struct
    // exists, then return it
    assert(controller.full_timing_info);
    return controller.full_timing_info.get();
}


auto fetch::detail::abort_fetch_controller(
        fetch_controller_t& controller,
        ext::optional<dom::other::dom_exception> error)
        -> void
{
    // to abort the 'controller', set its 'state' to the ABORTED state
    using enum dom::detail::dom_exception_error_t;
    controller.state = fetch_controller_state_t::ABORTED;
    auto fallback_error = dom::other::dom_exception{u8"", ABORT_ERR};
    auto abort_error = error.value_or(fallback_error);

    // TODO

}


auto fetch::detail::terminate_fetch_controller(fetch_controller_t& controller) -> void
{
    // to abort the 'terminated', set its 'state' to the TERMINATED state
    controller.state = fetch_controller_state_t::TERMINATED;
}


auto fetch::detail::is_aborted(fetch_params_t& params) -> ext::boolean
{
    // a 'controller' is aborted if its 'state' is ABORTED
    return params.controller->state == fetch_controller_state_t::ABORTED;
}


auto fetch::detail::is_cancelled(fetch_params_t& params) -> ext::boolean
{
    // a 'controller' is cancelled if its 'state' is ABORTED or TERMINATED
    return params.controller->state == fetch_controller_state_t::ABORTED || params.controller->state == fetch_controller_state_t::TERMINATED;
}


auto fetch::detail::is_cors_safelisted_method(
        ext::string_view method)
        -> ext::boolean
{
    auto cors_safelisted_methods = {u"GET", u"HEAD", u"POST"};
    return ranges::contains(cors_safelisted_methods, normalize_method(method));
}


auto fetch::detail::is_forbidden_method(
        ext::string_view method)
        -> ext::boolean
{
    auto forbidden_methods = {u"CONNECT", u"TRACE", u"TRACK"};
    return ranges::contains(forbidden_methods, normalize_method(method));
}


auto fetch::detail::normalize_method(
        ext::string_view method)
        -> ext::string
{
    return method | ranges::views::uppercase | ranges::to<ext::string>();
}


auto fetch::detail::translate_potential_destination(
        ext::string_view potential_destination)
        -> ext::string
{
    return_if (potential_destination == u"fetch") u"";
    ASSERT (magic_enum::enum_contains<destination_t>(potential_destination));
    return potential_destination;
}


auto fetch::detail::create_opaque_timing_info(
        fetch_timing_info_t& timing_info)
        -> std::unique_ptr<fetch_timing_info_t>
{
    auto opaque_timing_info = std::make_unique<fetch_timing_info_t>();
    opaque_timing_info->start_time                 = timing_info.start_time;
    opaque_timing_info->post_redirect_start_time   = timing_info.start_time;
    return std::move(opaque_timing_info);
}


template <ext::callable F>
auto fetch::detail::queue_fetch_task(
        F&& steps,
        html::detail::task_queue_t& task_destination)
        -> void
{
    task_destination.queue.template emplace(std::forward<F>(steps));
}


template <ext::callable F>
auto fetch::detail::queue_fetch_task(
        F&& steps,
        v8::Local<v8::Object> task_destination)
        -> void
{
    dom::detail::queue_global_task(html::detail::networking_task_source, task_destination, std::forward<F>(steps));
}

