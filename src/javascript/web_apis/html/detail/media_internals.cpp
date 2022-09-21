#include "media_internals.hpp"

#include "ext/ranges.hpp"

#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(media_source)

#include "dom/other/dom_exception.hpp"
#include "dom/detail/event_internals.hpp"
#include "dom/detail/observer_internals.hpp"

#include "fetch/detail/body_internals.hpp"
#include "fetch/detail/fetch_internals.hpp"
#include "fetch/detail/request_internals.hpp"

#include "file_api/detail/blob_internals.hpp"

#include "html/elements/html_audio_element.hpp"
#include "html/elements/html_media_element.hpp"
#include "html/elements/html_video_element.hpp"
#include "html/detail/miscellaneous_internals.hpp"

#include "media_source/detail/algorithm_internals.hpp"
#include "media_source/media_source.hpp"
#include "media_source/media_source_handle.hpp"

#include "miscellaneous_internals.hpp"
#include "url/detail/url_internals.hpp"

#include <range/v3/action/remove.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/for_each.hpp>


auto html::detail::media_element_load_algorithm(
        elements::html_media_element* element)
        -> void
{
    /* MEDIA_PLAYBACK_QUALITY BEGIN*/
    if (decltype(auto) video_element = dynamic_cast<elements::html_video_element*>(element))
    {
        video_element->m_total_video_frame_count = 0;
        video_element->m_dropped_video_frame_count = 0;
    }
    /* MEDIA_PLAYBACK_QUALITY END*/

    // TODO : abort running instances of this algorithm

    // Get the pending tasks of the HTMLMediaElement (each element has its own task queue so that mulitple media items
    // don't block each other. Filter the tasks so that only tasks that resolve or reject pending promises are kept. For
    // each of these tasks, invoke the task-function, and remove the task from the HTMLMediaElement's task queue.
    decltype(auto) pending_tasks = ext::vector<detail::task_t>{element->m_media_element_event_task_source};
    pending_tasks
            | ranges::views::filter([](auto&& task) {return false; /* TODO */})
            | ranges::views::for_each(ext::invoke{})
            | ranges::views::for_each([](auto&& task) {element->m_media_element_event_task_source |= ranges::actions::remove(task);});

    // If the network state of the HTMLMEdiaElement is IDLE or LOADING, then queue an element task for the 'element'
    // with the steps to fire an abort event at the HTMLMediaElement; this is because another resource is now being
    // fetched, so abort whatever is currently being done, and continue on.
    if (element->network_state() == element->NETWORK_IDLE || element->network_state() == element->NETWORK_LOADING)
        dom::detail::queue_media_element_task(element, [element] {dom::detail::fire_event("abort", element);});

    // If the network state isn't EMPTY, then prepare it for the new resource. Handle things like if the
    // HTMLMediaElement is paused/seeking or not, the ready state etc.
    if (element->network_state() != element->NETWORK_EMPTY)
    {
        // Queue a media task that fires an event notifiying the user that the HTMLMediaElement is being emptied (and
        // prepared for the new resource).
        dom::detail::queue_media_element_task(element, [element] {dom::detail::fire_event("emptied", element);});
        // TODO : abort fetching processes

        // If the HTMLMediaElement's provider is a MediaSource object, then detach it from the HTMLMediaElement (no
        // longer valid for the new resource being fetched)
        if (ext::holds_alternative<media::source::media_source*>(element->m_assigned_media_provider_object))
            media::detail::detach_from_media_element(ext::get<media::source::media_source*>(element->m_assigned_media_provider_object));

        // Tell the HTMLMediaElement to forget current track resources, and set the ready state to HAVE_NOTHING, because
        // the 'element' will be empty just ebfore the new resource if fetched.
        forget_media_element_media_resource_specific_tracks(element);
        element->ready_state = element->HAVE_NOTHING;

        // If the element isn't paused, then pause it, take all of the pending play promises from the HTMLMediaElement,
        // and reject them, with a ABORT_ERR DomException.
        if (!element->paused())
        {
            element->paused = true;
            auto promises = take_pending_play_promises(element);
            reject_pending_play_promises(take_pending_play_promises(element), dom::other::dom_exception{"", ABORT_ERR});
        }

        // Ensure that the HTMLMediaElement isn't seeking
        element->seeking = false;

        // Change the 'm_current_playback_position' and the 'm_official_playback_position' of the HTMLMediaElement, and
        // if the 'm_official_playback_position' was actually changed, then queue a emdia element task for "timeupdate";
        // this is because the HTMLMediaElement's official position must be reset before the new resource is fetched.
        auto watch_official_position = ext::attribute_watcher{element, &elements::html_media_element::m_official_playback_position};
        element->m_current_playback_position = 0;
        element->m_official_playback_position = 0;
        if (watch_official_position.has_changed())
            dom::detail::queue_media_element_task(element, ext::bind_front{dom::detail::fire_event, "timeupdate", element});

        // TODO : timeline offset

        // Set the duration of teh HTMLMEdiaElement to NaN (duration is unknown whilst the new resource is being
        // fetched).
        element->duration = decltype(element->duration)::value_t::nan();
    }

    // Set the playback rate to its default, any error that there mightv'e been from the previous resource to nullptr,
    // the autoplay flag to true, and select the new resource for this HTMLMediaElement.
    element->playback_rate = element->default_playback_rate();
    element->error = nullptr;
    element->m_can_autoplay_flag = true;
    resource_selection_algorithm(element);
}


auto html::detail::resource_fetch_algorithm(
        elements::html_media_element* element,
        ext::variant<url::detail::url_t, dom_object*> url_or_media_provider)
        -> void
{
    enum class resource_mode_t {LOCAL, REMOTE};
    using enum resource_mode_t;

    auto mode = ext::holds_alternative<void*>(url_or_media_provider)
            || ext::get<url::detail::url_t>(url_or_media_provider).blob_url_entry.get()
            && ext::visit([](auto* object) -> bool {return object;}, ext::get<url::detail::url_t>(url_or_media_provider).blob_url_entry->object)
            ? LOCAL : REMOTE;

    *element->audio_tracks() |= ranges::actions::filter(is_media_resource_specific_text_track);
    *element->video_tracks() |= ranges::actions::filter(is_media_resource_specific_text_track);
    *element->text_tracks () |= ranges::actions::filter(is_media_resource_specific_text_track);

    if (mode == REMOTE)
    {
        {
            element->network_state = element->NETWORK_IDLE;
            dom::detail::queue_media_element_task(element, [element] {dom::detail::fire_event("suspend", element);});
            dom::detail::queue_media_element_task(element, [element] {element->m_delaying_load_event_flag = false;});

            // TODO : wait for task
            // TODO : wait for event
            element->m_delaying_load_event_flag = true;
            element->network_state = element->NETWORK_LOADING;
        }

        decltype(auto) current_media_resource = ext::get<url::detail::url_t>(url_or_media_provider);
        decltype(auto) destination = dynamic_cast<elements::html_audio_element*>(element) ? fetch::detail::destination_t::AUDIO : fetch::detail::destination_t::VIDEO;
        decltype(auto) request = html::detail::create_potential_cors_request(current_media_resource, destination, element->cross_origin());
        decltype(auto) document = element->owner_document();

        JS_REALM_GET_RELEVANT(document);
        request.client = document_relevant_settings_object;
        // TODO : byteRange
        auto byte_range = ext::string{};

        auto process_response = [document_relevant_global_object, destination, element, byte_range = std::move(byte_range)](fetch::detail::response_t& response)
        {
            auto update_media = [element]
            {dom::detail::queue_media_element_task(element, [element] {media_data_processing_steps_list(element);});};

            auto finalize = [&response, document_relevant_global_object, destination, update_media = std::move(update_media)]
            {fetch::detail::report_timing(response, document_relevant_global_object, destination); update_media();};

            auto process_end_of_media = [finalize = std::move(finalize)]
            {finalize(); /* TODO */ };

            verify_media_response(response, element, byte_range)
                    ? fetch::detail::incrementally_read_body(*response.body, std::move(update_media), std::move(process_end_of_media), std::move(finalize), document_relevant_global_object)
                    : finalize();

            // TODO : media data?
        };

        fetch::detail::fetch(&request, nullptr, nullptr, nullptr, process_response);

        // TODO
    }

    else if (mode == LOCAL)
    {
        // TODO

        /* MEDIA_SOURCE BEGIN*/ // Inject at "otherwise (mode is local) step

        if (ext::holds_alternative<url::detail::url_t>(url_or_media_provider)
                && dynamic_cast<media::source::media_source*>(ext::get<url::detail::url_t>(url_or_media_provider).object.get())
                || dynamic_cast<media::source::media_source*>(ext::get<dom_object*>(url_or_media_provider))
                || dynamic_cast<media::source::media_source_handle*>(ext::get<dom_object*>(url_or_media_provider)))
        {
            decltype(auto) url_underlying_provider = ext::get<url::detail::url_t>(url_or_media_provider).object.get();
            JS_REALM_GET_CREATION(url_underlying_provider);
            decltype(auto) handle = dynamic_cast<media::source::media_source_handle*>(ext::get<dom_object*>(url_or_media_provider));
            decltype(auto) source = dynamic_cast<media::source::media_source*>(ext::get<dom_object*>(url_or_media_provider));

            if (ext::holds_alternative<url::detail::url_t>(url_or_media_provider)
                    && dynamic_cast<media::source::media_source*>(ext::get<url::detail::url_t>(url_or_media_provider).object.get())
                    && v8pp::from_v8<html::workers::dedicated_worker_global_scope*>(url_underlying_provider_creation_agent, url_underlying_provider_creation_global_object))
                media_data_processing_steps_list(element, detail::media_data_processing_t::CANNOT_BE_FETCHED);

            else if (handle && handle->s_detached())
                media_data_processing_steps_list(element, detail::media_data_processing_t::CANNOT_BE_FETCHED);

            else if (handle->m_source->s_has_ever_been_detached())
                media_data_processing_steps_list(element, detail::media_data_processing_t::CANNOT_BE_FETCHED);

            else if (source->ready_state() != media::detail::ready_state_t::CLOSED)
                media_data_processing_steps_list(element, detail::media_data_processing_t::CANNOT_BE_FETCHED);

            else
            {
                source->s_has_event_been_detached = true;
                element->m_delaying_load_event_flag = false;

                JS_REALM_GET_CREATION(source);
                if (decltype(auto) dedicated_worker_global_scope = v8pp::from_v8<html::workers::dedicated_worker_global_scope*>(source_creation_agent, source_creation_global_object))
                {
                    element->s_channel_with_worker = std::make_unique<html::messaging::message_channel>();
                    element->s_port_to_worker = element->s_channel_with_worker()->port1();
                    auto serialized_port2 = html::detail::structured_serialize_with_transfer(element->s_channel_with_worker()->port2());

                    dom::detail::queue_task(dedicated_worker_global_scope->m_task_queue, [source, dedicated_worker_global_scope]
                    {
                        auto deserialized = html::detail::structured_deserialize_with_transfer(serialized_port2, source_creation_context);
                        source->s_port_to_main = element->s_channel_with_worker(); // TODO: deserialized
                        source->ready_state = media::detail::ready_state_t::OPEN;
                        dom::detail::queue_task(dedicated_worker_global_scope->m_task_queue,
                                [source, dedicated_worker_global_scope]
                                {dom::detail::fire_event("sourceopen", source);});
                    });
                }

                else if (decltype(auto) window = v8pp::from_v8<dom::nodes::window*>(source_creation_agent, source_creation_global_object))
                {
                    element->s_channel_with_worker = nullptr;
                    element->s_port_to_worker = nullptr;
                    source->s_port_to_main = nullptr;
                    source->ready_state = media::detail::ready_state_t::OPEN;
                    dom::detail::queue_task(dedicated_worker_global_scope->m_task_queue,
                            [source, dedicated_worker_global_scope]
                            {dom::detail::fire_event("sourceopen", source);});
                }
            }
        }

        // || dynamic_cast<media::source::media_source*>(ext::get<void*>(url_or_media_provider))
        // || dynamic_cast<media::source::media_source_handle*>(ext::get<void*>(url_or_media_provider)))

        /* MEDIA_SOURCE END*/
    }
}
