#include "image_internals.hpp"

#include "ext/ranges.hpp"
#include "javascript/environment/reflection.hpp"

#include "dom/detail/event_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/observer_internals.hpp"

#include "fetch/detail/request_internals.hpp"

#include "html/detail/lazy_loading_internals.hpp"
#include "html/detail/miscellaneous_internals.hpp"
#include "html/detail/scripting_internals.hpp"
#include "html/detail/task_internals.hpp"
#include "html/elements/html_image_element.hpp"
#include "html/elements/html_source_element.hpp"

#include "referrer_policy/referrer_policy.hpp"

#include <magic_enum.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/action/unique.hpp>
#include <range/v3/view/map.hpp>


auto html::detail::image_internals::is_available(
        image_request& request)
        -> ext::boolean
{
    // an image request is said to be available if its state is [PARTIALLY/COMPLETELY]_AVAILABLE
    using enum state_t;
    auto available_states = {PARTIALLY_AVAILABLE, COMPLETELY_AVAILABLE};
    return ranges::contains(available_states, request.state);
}


auto html::detail::image_internals::determine_density_corrected_intrinsic_width_and_height(
        elements::html_image_element* element)
        -> void
{
    // adjust the width and height of the preferred density corrected dimensions, by dividing the values in the struct
    // (width and height), by the current pixel density of the HTMLImageElement's current request
    auto dimensions = element->m_current_request.preferred_density_corrected_dimensions;
    // TODO : [CSS-IMAGES-3] intrinsic dimensions
    dimensions.width /= element->m_current_request->current_pixel_density;
    dimensions.height /= element->m_current_request->current_pixel_density;
    return dimensions;
}


auto html::detail::image_internals::update_image_data(
        elements::html_image_element* element,
        ext::boolean_view restart_animation_flag)
        -> void
{
    using enum state_t;
    using enum fetch::detail::request_internals::mode_t;

    if (!dom::detail::node_internals::is_document_fully_active(element->owner_document()))
    {
        /*
         * TODO : continue running in a thread (move next steps into a lambda and call from .push task in a thread pool)
         * TODO : wait until element->owner_document() is fully active -> easy
         * TODO : somehow detect if another instance of this algorithm is running (counter in namespace?)
         * TODO : queue a microtask to continue the rest of the method
         */
    }

    // if the system doesn't support images, or images have been disabled for a reason, then the current and pending
    // requests are instantly cancelled, the current request is sent to the UNAVAILABLE state, because although it
    // exists, it cannot be used, and the pending request is set to nullptr - no point of it existing
    if (!_IMAGES_SUPPORTED)
    {
        abort_image_request(*element->m_current_request);
        abort_image_request(*element->m_pending_request);
        element->m_current_request->state = UNAVAILABLE;
        element->m_pending_request.reset();
    }

    // the selected source is the element's 'src', unless the element is using the 'srcset' attribute of has a
    // HTMLPictureElement parent, in which case there is no 'selected_source', and the 'selected_pixel_density' is set
    // to 0.0
    auto [selected_source, selected_pixel_density] = !uses_srcset_or_picture(element) // TODO : ext:number<double>
            ? tuplet::make_tuple(element->src(), 1.0)
            : tuplet::make_tuple(ext::string{}, 0.0);

    // set the last selected source of the elment to the new 'selected_source'
    element->m_last_selected_source = selected_source;

    // steps for when the selected source is valid, ie the element isn't using the 'srcset' attribute and doesn't have
    // a HTMLPictureElement parent
    if (!selected_source.empty())
    {
        // parse the selected source relative to the elements document, and extract the string ans url from the
        // resulting tuple
        auto url_object = miscellaneous_internals::parse_url(selected_source, element->owner_document());
        auto url_string = url_object.first;
        auto url_record = url_object.second;

        // steps for when the url is invalid, ie a parsing failure, because the url record evaluates to a false boolean
        if (!url_record)
        {
            auto cross_origin = magic_enum::enum_cast<fetch::detail::request_internals::mode_t>(element->cross_origin());
            auto key = tuplet::make_tuple(url_string, cross_origin, cross_origin != NO_CORS ? element->owner_document()->m_origin : url::url_object(""));
            if (ranges::contains(element->owner_document()->m_list_of_available_images | ranges::views::keys, key))
            {
                auto& matching_key = ranges::first_where(
                        element->owner_document()->m_list_of_available_images | ranges::views::keys,
                        [&key](auto& trial_key) {return *trial_key == key;});

                matching_key.ignore_higher_layer_caching_flag = ext::boolean::FALSE();
                abort_image_request(*element->m_current_request);
                abort_image_request(*element->m_pending_request);
                element->m_current_request = std::make_unique<image_request>(
                        COMPLETELY_AVAILABLE,
                        {}, {1}, {},
                        element->owner_document()->m_list_of_available_images.at(matching_key));
                element->m_current_request.reset();

                prepare_image_for_presentation(*element->current_request, element);
                element->m_current_request->current_pixel_density = selected_pixel_density;

                dom::detail::observer_internals::queue_element_task(
                        detail::task_internals::dom_manipulation_task_source(),
                        element,
                        [&restart_animation_flag, &element, &url_record]
                        {
                            if (restart_animation_flag) restart_animation(element);
                            element->m_current_request->url = url_record;
                            dom::detail::event_internals::fire_event("load", element);
                        });

                // TODO : abort an algorithm
            }
        }
    }

    dom::detail::observer_internals::queue_microtask([&element, &restart_animation_flag]
    {
        // TODO : return if this algorithm is already running
        auto [selected_source, selected_pixel_density] = select_image_source(element);
        if (!selected_source)
        {
            element->m_current_request->state = BROKEN;
            abort_image_request(*element->m_current_request);
            abort_image_request(*element->m_pending_request);
            element->m_pending_request.reset();

            dom::detail::observer_internals::queue_element_task(detail::task_internals::dom_manipulation_task_source(), element, [&element]
            {
                element->m_current_request->url = "";
                JS_REALM_GET_RELEVANT(element)
                if (reflect_has_attribute_value(element, "src", element_relevant) || uses_srcset_or_picture(element))
                    dom::detail::event_internals::fire_event("error", element);
            });

            return;
        }

        auto url_object = miscellaneous_internals::parse_url(selected_source, element->owner_document());
        auto url_record = url_object.second;
        if (!url_record)
        {
            abort_image_request(*element->m_current_request);
            abort_image_request(*element->m_pending_request);
            element->m_current_request->state = BROKEN;
            element->m_pending_request.reset();

            dom::detail::observer_internals::queue_element_task(detail::task_internals::dom_manipulation_task_source(), element, [&element]
            {
                element->m_current_request->url = selected_source;
                dom::detail::event_internals::fire_event("error", element);
            });
            return;
        }

        return_if (element->m_pending_request && element->m_pending_request->url == url_record);
        if (element->m_current_request->state == PARTIALLY_AVAILABLE && element->m_current_request->url == url_record)
        {
            abort_image_request(*element->m_pending_request);
            if (restart_animation_flag)
                dom::detail::observer_internals::queue_element_task(detail::task_internals::dom_manipulation_task_source(), element, [&element] {restart_animation(element);});
            return;
        }

        if (element->m_pending_request)
            abort_image_request(*element->m_pending_request);

        image_request new_image_request{.url = url_record};
        element->m_current_request->state == UNAVAILABLE || element->m_current_request->state == BROKEN
                ? element->m_current_request.reset(&new_image_request)
                : element->m_pending_request.reset(&new_image_request);

        JS_REALM_GET_RELEVANT(element)
        using destination_t = fetch::detail::request_internals::destination_t;
        using initiator_t = fetch::detail::request_internals::initiator_t;
        auto request = miscellaneous_internals::create_potential_cors_request(url_record, destination_t::IMAGE, magic_enum::enum_cast<fetch::detail::request_internals::mode_t>(element->cross_origin()));
        request.client = element_relevant_global_object;
        request.initiator = uses_srcset_or_picture(element) ? initiator_t::IMAGESET : static_cast<initiator_t>(NULL);
        request.referrer_policy = magic_enum::enum_cast<referrer_policy::referrer_policy_t>(element->referrer_policy());

        using lazy_loading_t = lazy_loading_internals::lazy_loading_t;
        auto delay_load_event = magic_enum::enum_cast<lazy_loading_t>(element->loading()) == lazy_loading_t::EAGER
                || scripting_internals::is_scripting_disabled(element);

        if (lazy_loading_internals::will_lazy_load_element_steps(element))
            ; // TODO : finish method
    });
}


auto html::detail::image_internals::abort_image_request(
        image_request& request)
        -> void
{
    request.image_data; // TODO : clear it
    // TODO : abort fetching algorithms
}


auto html::detail::image_internals::upgrade_pending_request_to_current_request(
        elements::html_image_element* element)
        -> void
{
    // move the raw pointer from the pending request into the current request (no copy or moving of unique pointer has
    // to happen), and reset the pointer in the pending request to a nullptr (TODO : what happens to pointer in current
    //  request?)
    element->m_current_request.reset(element->m_pending_request.get());
    element->m_pending_request.reset();
}


auto html::detail::image_internals::select_image_source(
        elements::html_image_element* element)
        -> ext::tuple<url::url_object, double>
{
    update_source_set(element);
    return_if (element->m_source_set.empty()) tuplet::make_tuple("", -1.0);
    return select_image_source_from_source_set(element->m_source_set);
}


auto html::detail::image_internals::select_image_source_from_source_set(
        ext::set<image_source*>& source_set)
        -> ext::tuple<url::url_object, double>
{
    source_set |= ranges::actions::unique([](image_source* left, image_source* right) {return left->pixel_density_descriptor == right->pixel_density_descriptor;});
    auto selected_source = *source_set.begin(); // TODO : *begin()?
    return tuplet::make_tuple(selected_source->url_record, selected_source->pixel_density_descriptor); // TODO : correct attributes?Magnesium
}


auto html::detail::image_internals::create_source_set(
        const ext::string& default_source,
        const ext::string& src_set,
        const ext::string& sizes)
        -> ext::set<image_source*>
{
    auto source_set = parse_source_set_attribute(src_set);
    auto source_size = parse_sizes_attribute(sizes);

    if (!default_source.empty()
            && !ranges::contains(source_set | ranges::views::transform([](image_source* source) {return source->pixel_density_descriptor;}), "1")
            && ranges::all_of(source_set, [](image_source* source) {return source->width_descriptor == "0";}))
        source_set.emplace(state_t{}, miscellaneous_internals::parse_url(default_source, nullptr)); // TODO : is this emplaced correctly?

    return normalize_source_densities(source_set);
}


auto html::detail::image_internals::update_source_set(
        type_is<elements::html_image_element*, elements::html_link_element*> auto* element)
        -> void
{
    element->m_source_set = {};
    auto is_element_image = element->local_name() == "image";
    auto elements = is_element_image && element->parent_node()->local_name() == "picture"
            ? ext::span<dom::nodes::element*>{element}
            : *element->children();

    for (dom::nodes::element* child: elements)
    {
        if (child == element)
        {
            JS_REALM_GET_RELEVANT(element)

            ext::string default_source = is_element_image && reflect_has_attribute_value(element, "src", element_relevant)
                    ? element->src()
                    : reflect_has_attribute_value(element, "href", element_relevant)
                    ? element->href()
                    : "";

            ext::string src_set = is_element_image && reflect_has_attribute_value(element, "srcset", element_relevant)
                    ? element->srcset()
                    : reflect_has_attribute_value(element, "image_srcset", element_relevant)
                    ? element->image_srcset()
                    : "";

            ext::string sizes = is_element_image && reflect_has_attribute_value(element, "sizes", element_relevant)
                    ? element->sizes()
                    : reflect_has_attribute_value(element, "image_sizes", element_relevant)
                    ? element->image_sizes()
                    : "";

            element->m_source_set = create_source_set(default_source, src_set, sizes);
            return;
        }

        JS_REALM_GET_RELEVANT(child)
        continue_if(child->local_name() != "source");
        continue_if(!reflect_has_attribute_value(child, "srcset", child_relevant));

        auto* cast_child = dynamic_cast<elements::html_source_element*>(child);

        auto source_set = parse_source_set_attribute(cast_child->srcset());
        continue_if(source_set.empty());
        continue_if(reflect_has_attribute_value(cast_child, "media", child_relevant) /* TODO && not matching environment */);

        auto source_size = parse_sizes_attribute(cast_child->sizes());
        continue_if(reflect_has_attribute_value(cast_child, "type", child_relevant) /* TODO && type == ... */);

        // TODO : width and height
        normalize_source_densities(source_set);
        element->m_source_set = source_set;
        return;
    }
}
