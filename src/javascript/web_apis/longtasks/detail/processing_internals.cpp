#include "processing_internals.hpp"

#include "ext/hashing.hpp"

#include "javascript/environment/environment_settings.hpp"
#include "javascript/environment/realms_2.hpp"

#include "dom/nodes/document.hpp"
#include "html/detail/context_internals.hpp"

#include <range/v3/view/transform.hpp>


auto longtasks::detail::report_long_tasks(
        hr_time::dom_high_res_time_stamp start_time,
        hr_time::dom_high_res_time_stamp end_time,
        ext::vector_view<html::detail::browsing_context_t*> browsing_contexts,
        html::detail::task_t&& task) -> void
{
    return_if (end_time - start_time < 50);
    auto destination_realms = ext::set<ext::tuple<v8::Local<v8::Context>, ext::boolean>>{};

    for (decltype(auto) topmost_browsing_context: browsing_contexts)
    {
        decltype(auto) active_document = html::detail::active_document(*topmost_browsing_context);
        decltype(auto) descendant_browsing_contexts = html::detail::descendant_browsing_contexts(active_document);

        {
            JS_REALM_GET_RELEVANT(active_document);
            destination_realms.emplace(ext::make_tuple(active_document_relevant_realm, ext::boolean::FALSE_()));
        }

        for (decltype(auto) descendant_browsing_context: descendant_browsing_contexts)
        {
            auto descendant_browsing_context_active_document = html::detail::active_document(*topmost_browsing_context);
            JS_REALM_GET_RELEVANT(descendant_browsing_context_active_document);

            decltype(auto) settings_object = v8pp::from_v8<javascript::environment::settings_t*>(
                    descendant_browsing_context_active_document_relevant_agent,
                    descendant_browsing_context_active_document_relevant_settings_object);

            destination_realms.emplace(ext::make_tuple(
                    descendant_browsing_context_active_document_relevant_realm,
                    settings_object->cross_origin_isolated_capability));
        }
    }

    for (auto&& [destination_realm, cross_origin_isolated_capability]: destination_realms)
    {
        auto name = ext::string{};
        auto culprit_settings = javascript::environment::settings_t();

        {
            // TODO
        }
    }
}
