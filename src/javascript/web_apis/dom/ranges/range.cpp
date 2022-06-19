#include "range.hpp"

#include <javascript/environment/realms.hpp>
#include <web_apis/dom/nodes/document.hpp>

namespace dom::nodes {class window;}


dom::node_ranges::range::range()
{
    bind_get(common_ancestor_container);

    start_container = javascript::environment::realms::realm<nodes::window*>::current_realm(this).get<nodes::document*>("associated_document");
    end_container   = javascript::environment::realms::realm<nodes::window*>::current_realm(this).get<nodes::document*>("associated_document");
    start_offset    = 0;
    end_offset      = 0;
}
