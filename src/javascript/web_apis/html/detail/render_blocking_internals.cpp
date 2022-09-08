#include "render_blocking_internals.hpp"

#include "ext/ranges.hpp"

#include "dom/nodes/element.hpp"
#include "dom/nodes/document.hpp"
#include "hr_time/detail/time_internals.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/action/remove.hpp>


auto html::detail::allows_adding_render_blocking_elements(
        dom::nodes::document* document)
        -> ext::boolean
{
    auto html_content_type = document->content_type() == "text/html";
    auto body_element      = document->body();
    return html_content_type && !body_element;
}


auto html::detail::is_render_blocked(
        dom::nodes::document* document)
        -> ext::boolean
{
    // if the Document allows render blocking elements (or there are elements in the Document's set of blocking
    // elements), but the rendering has timed out, then return true, as the Document is blocked from processing due to
    // rendering taking too long (or freezing etc)
    JS_REALM_GET_RELEVANT(document);
    auto document_allows  = !document->m_render_blocking_elements.empty() || allows_adding_render_blocking_elements(document);
    auto render_timed_out = hr_time::detail::current_hr_time(document_relevant_global_object) < 1000; // TODO : change 1000
    return document_allows && render_timed_out;
}


auto html::detail::is_render_blocking(
        dom::nodes::element* element)
        -> ext::boolean
{
    // if the Element's owner document is currently render blocked, and this Element belongs to the Document's set of
    // render blocking elements, then this Element is causing the Document to be render blocked, and is therefore a
    // render blocking element
    auto document_blocked = is_render_blocked(element->owner_document());
    auto belong_to_documents_render_elements = ranges::contains(element->owner_document()->m_render_blocking_elements, element);
    return document_blocked && belong_to_documents_render_elements;
}


auto html::detail::block_rendering(
        dom::nodes::element* element)
        -> ext::boolean
{
    // if the Element's owner document allows render blocking elements to be added to it, then add the Element to the
    // Document's set of render blocking elements
    auto* document = element->owner_document();
    if (allows_adding_render_blocking_elements(document))
        document->m_render_blocking_elements.insert(element);
}


auto html::detail::unblock_rendering(
        dom::nodes::element* element)
        -> ext::boolean
{
    // remove the Element from its owner document's set of blocking elements
    auto* document = element->owner_document();
    document->m_render_blocking_elements |= ranges::actions::remove(element);
}
