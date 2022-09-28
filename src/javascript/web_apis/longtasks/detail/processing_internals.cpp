#include "processing_internals.hpp"

#include "javascript/environment/realms_2.hpp"

#include "html/detail/context_internals.hpp"

#include <range/v3/view/transform.hpp>


auto longtasks::detail::report_long_tasks(
        hr_time::dom_high_res_time_stamp start_time,
        hr_time::dom_high_res_time_stamp end_time,
        ext::vector_view<html::detail::browsing_context_t*> browsing_contexts,
        html::detail::task_t&& task) -> void
{
    return_if (end_time - start_time < 50);
    auto destination_realms = ext::set<v8::Local<v8::Context>>{};

    for (decltype(auto) topmost_browsing_context: browsing_contexts)
    {
        decltype(auto) active_document = html::detail::active_document(*topmost_browsing_context);
        JS_REALM_GET_RELEVANT(active_document);

        destination_realms.emplace(active_document_relevant_realm);
    }
}
