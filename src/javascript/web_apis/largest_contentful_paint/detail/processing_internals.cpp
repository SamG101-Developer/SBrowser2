#include "processing_internals.hpp"

#include "ext/hashing.hpp"

#include INCLUDE_INNER_TYPES(hr_time)

#include "css/geometry/dom_rect_readonly.hpp"

#include "dom/nodes/document.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/window.hpp"

#include "ext/number.hpp"
#include "fetch/request.hpp"

#include "html/detail/context_internals.hpp"
#include "html/detail/document_internals.hpp"
#include "largest_contentful_paint/largest_contentful_paint.hpp"
#include "performance_timeline/detail/processing_internals.hpp"


auto largest_contentful_paint::detail::potentially_add_largest_contentful_paint_entry(
        css::geometry::dom_rect_readonly* intersection_rect,
        fetch::request* request,
        hr_time::dom_high_res_time_stamp render_time,
        hr_time::dom_high_res_time_stamp load_time,
        dom::nodes::element* element,
        dom::nodes::document* document) -> void
{
    auto content_identifier = ext::make_tuple(element, request);
    return_if (document->d_func()->content_set.contains(content_identifier));
    document->d_func()->content_set.emplace(std::move(content_identifier));

    JS_REALM_GET_RELEVANT(document);
    decltype(auto) window = v8pp::from_v8<dom::nodes::window*>(document_relevant_agent, document_relevant_global_object);
    return_if (window->d_func()->has_dispathced_scroll_event || window->d_func()->has_dispatched_input_event);

    auto url = request->d_func()->request_url;
    auto id = element->d_func()->id;
    auto width = intersection_rect->d_func()->rect.width();
    auto height = intersection_rect->d_func()->rect.height();
    auto size = width * height;
    auto root = html::detail::active_document(*document->d_func()->browsing_context);
    auto root_width = css::cssom_view::viewport(root).d_func()->rect.width();
    auto root_height = css::cssom_view::viewport(root).d_func()->rect.height();
    return_if (root_width * root_height == size);

    if (request)
    {
        auto concrete_dimensions = css::detail::concrete_object_size(request, element);
        auto visible_dimensions = css::detail::adjusted_for_positioning(css::detail::css_box(element));

        // TODO
    }

    return_if (size <= document->d_func()->largest_contentful_paint_size);

    auto content_info_map = ext::map<ext::string, ext::any>
    {
            {"size", size},
            {"url", url},
            {"id", id},
            {"renderTime", render_time},
            {"loadTime", load_time},
            {"element", element}
    };

    create_largest_contentful_paint_entry(std::move(content_info_map), document);
}


auto largest_contentful_paint::detail::create_largest_contentful_paint_entry(
        ext::map<ext::string, ext::any>&& construct_map,
        dom::nodes::document* document) -> void
{
    document->d_func()->largest_contentful_paint_size = construct_map["size"].to<ext::number<int>>();
    auto entry = largest_contentful_paint{};
    entry->d_func()->size = construct_map["size"].to<ext::number<int>>();
    entry->d_func()->url = std::move(construct_map["url"].to<ext::string>());
    entry->d_func()->id = std::move(construct_map["id"].to<ext::string>());
    entry->d_func()->render_time = construct_map["renderTime"].to<hr_time::dom_high_res_time_stamp>();
    entry->d_func()->load_time = construct_map["loadTime"].to<hr_time::dom_high_res_time_stamp>();
    entry->d_func()->element = construct_map["element"].to<dom::nodes::element*>();

    performance_timeline::detail::queue_performance_entry(&entry);
}
