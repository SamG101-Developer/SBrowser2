#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_DETAIL_EDIT_CONTEXT_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_DETAIL_EDIT_CONTEXT_INTERNALS_HPP

namespace edit_context {class edit_context;}


namespace edit_context::detail
{
    auto when_edit_context_activated(
            edit_context::edit_context* edit_context)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_DETAIL_EDIT_CONTEXT_INTERNALS_HPP
