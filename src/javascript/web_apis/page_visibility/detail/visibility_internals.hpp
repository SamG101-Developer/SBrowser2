#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAGE_VISIBILITY_DETAIL_VISIBILITY_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAGE_VISIBILITY_DETAIL_VISIBILITY_INTERNALS_HPP

#include "ext/assertion.hpp"
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(page_visibility)


namespace page_visibility::detail
{
    auto determine_page_visibility(
            const html::detail::browsing_context_t& context)
            -> detail::visibility_state_t;

    auto on_browser_context_document_visibility_state_change()
            -> void;

    auto now_visible_algorithm()
            -> void;

    auto now_hidden_algorithm()
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAGE_VISIBILITY_DETAIL_VISIBILITY_INTERNALS_HPP
