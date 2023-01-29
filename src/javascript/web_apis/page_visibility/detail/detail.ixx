module;
#include "ext/macros.hpp"


export module apis.page_visibility.detail;
import apis.page_visibility.types;
import apis.html.types;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(page_visibility)
{
    auto determine_page_visibility(const html::detail::browsing_context_t& context)-> detail::visibility_state_t;
    auto on_browser_context_document_visibility_state_change() -> void;
    auto now_visible_algorithm() -> void;
    auto now_hidden_algorithm() -> void;
};
