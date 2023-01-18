#include "general_internals.hpp"







#include "fetch/detail/request_internals.hpp"
#include "html/detail/task_internals.hpp"


#include <range/v3/algorithm/contains.hpp>


fetch::detail::fetch_group_t::~fetch_group_t()
{
    using enum ranges::filter_compare_t;

    fetch_records
            | ranges::views::filter_eq<NE>(&fetch_record_t::controller, nullptr, ext::underlying)
            | ranges::views::filter([](fetch_record_t* record) {return !record->request->done_flag || !record->request->keep_alive;})
            | ranges::views::for_each([](fetch_record_t* record) {terminate_fetch_controller(*record->controller);});
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

