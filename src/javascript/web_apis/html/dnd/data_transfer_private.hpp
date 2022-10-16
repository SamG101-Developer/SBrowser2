#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include "ext/ranges.hpp"
#include INCLUDE_INNER_TYPES(html)
namespace html::dnd {class data_transfer_item;}


DEFINE_PRIVATE_CLASS(html::dnd, data_transfer) : virtual dom_object_private
{
    detail::drop_effect_t drop_effect;
    detail::effect_allowed_t effect_allowed;
    ext::vector<std::unique_ptr<data_transfer_item>> items;

    ranges::any_helpful_view<ext::string> types_array;
    std::unique_ptr<detail::drag_data_store_t> drag_data_store;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_PRIVATE_HPP
