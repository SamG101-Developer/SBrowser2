#include "range.hpp"

#include <javascript/environment/realms_2.hpp>
#include <web_apis/dom/nodes/document.hpp>

namespace dom::nodes {class window;}


dom::node_ranges::range::range()
{
    bind_get(common_ancestor_container);

    JS_REALM_GET_CURRENT
    start_container = javascript::environment::realms_2::get<nodes::document*>(current_global_object, "associated_document");
    end_container   = javascript::environment::realms_2::get<nodes::document*>(current_global_object, "associated_document");
    start_offset    = 0;
    end_offset      = 0;

    m_root = nullptr;
}
