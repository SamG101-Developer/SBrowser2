#pragma once
#ifndef SBROWSER2_RENDER_BLOCKING_INTERNALS_HPP
#define SBROWSER2_RENDER_BLOCKING_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
namespace dom::nodes {class document;}
namespace dom::nodes {class document_fragment;}
namespace dom::nodes {class element;}
namespace dom::nodes {class node;}


namespace html::detail
{
    auto allows_adding_render_blocking_elements(
            dom::nodes::document* document)
            -> ext::boolean;

    auto is_render_blocked(
            dom::nodes::document*)
            -> ext::boolean;

    auto is_render_blocking(
            dom::nodes::element* element)
            -> ext::boolean;

    auto block_rendering(
            dom::nodes::element* element)
            -> ext::boolean;

    auto unblock_rendering(
            dom::nodes::element* element)
            -> ext::boolean;

    auto being_rendered(
            const dom::nodes::node* node)
            -> ext::boolean;
}


#endif //SBROWSER2_RENDER_BLOCKING_INTERNALS_HPP
