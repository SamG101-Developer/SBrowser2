#include "context_internals.hpp"

#include "dom/nodes/document.hpp"


auto html::detail::context_internals::is_still_on_initial(
        browsing_context* context)
        -> ext::boolean
{
    // the browsing context object is still on its initial state if there is only 1 Document in the session history, and
    // the Document is still on it's initial (about:blank); acts as a wrapper to the Document's 'is_initial', but
    // requires that there is ony 1 Document
    return context->session_history.size() == 1 && context->session_history.front()->m_is_initial;
}
