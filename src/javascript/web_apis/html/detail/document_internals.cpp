#include "document_internals.hpp"

#include "dom/nodes/document.hpp"


auto html::detail::document_internals::is_cookie_averse_document(
        const dom::nodes::document* document)
        -> ext::boolean
{
    // a Document is a cookie averse document if it doesn't have a browsing context, and the scheme of the URL is not
    // HTTPS - this is because cookies need to be transported securely (HTTPS ensures this), and a browsing context
    // ensures that cookies are only shred to the correct Documents
    return !document->m_browsing_context || document->url->scheme() != "https";
}
