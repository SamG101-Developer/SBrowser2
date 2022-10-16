#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_DND_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_DND_INTERNALS_HPP

#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(html)
namespace dom::nodes {class event_target;}


namespace html::detail
{
    auto fire_dnd_event(
            ext::string&& e,
            dom::nodes::event_target* element,
            const detail::drag_data_store_t& data_store,
            dom::nodes::event_target* related_target = nullptr)
            -> void;
}


struct html::detail::drag_data_store_item_list_t
{
    drag_data_item_kind_t drag_data_item_kind;
    ext::string drag_data_item_type_string;
    ext::string data;
};


struct html::detail::drag_data_store_t
{
    drag_data_store_t();

    ext::vector<std::unique_ptr<drag_data_store_item_list_t>> drag_data_store_item_list;
    ext::string drag_data_store_default_feedback;
    std::unique_ptr<canvasing::image_bitmap> drag_data_store_image_bitmap;
    ext::pair<ext::number<double>, ext::number<double>> drag_data_store_hot_spot_coordinate;
    detail::drag_data_store_mode_t drag_data_store_mode;
    ext::string drag_data_store_allowed_effects_state;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_DND_INTERNALS_HPP
