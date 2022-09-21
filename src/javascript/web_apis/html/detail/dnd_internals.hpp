#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_DND_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_DND_INTERNALS_HPP

#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(html)
namespace dom::nodes {class event_target;}
namespace html::detail {class drag_data_store_t;}


namespace html::detail
{
    auto fire_dnd_event(
            ext::string&& e,
            dom::nodes::event_target* element,
            const detail::drag_data_store_t& data_store,
            dom::nodes::event_target* related_target = nullptr)
            -> void;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_DND_INTERNALS_HPP
