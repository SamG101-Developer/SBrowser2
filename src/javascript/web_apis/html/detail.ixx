module;
#include "ext/macros/pimpl.hpp"


export module apis.html.detail;
import apis.dom.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(html)
{
    auto allows_adding_render_blocking_elements(
            dom::document* document)
            -> ext::boolean;

    auto is_render_blocked(
            dom::document*)
            -> ext::boolean;

    auto is_render_blocking(
            dom::element* element)
            -> ext::boolean;

    auto block_rendering(
            dom::element* element)
            -> ext::boolean;

    auto unblock_rendering(
            dom::element* element)
            -> ext::boolean;

    auto being_rendered(
            const dom::node* node)
            -> ext::boolean;
}
