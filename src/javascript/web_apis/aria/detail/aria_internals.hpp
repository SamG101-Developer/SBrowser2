#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ARIA_DETAIL_ARIA_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ARIA_DETAIL_ARIA_INTERNALS_HPP

#include "ext/vector.hpp"
namespace dom::nodes {class element;}


namespace aria::detail
{
    auto when_assistive_technology_changes_focus(
            dom::nodes::element* element)
            -> void;

    auto owned_elements(
            dom::nodes::element* element)
            -> ext::vector<dom::nodes::element*>;

    auto owning_elements(
            dom::nodes::element* element)
            -> ext::vector<dom::nodes::element*>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ARIA_DETAIL_ARIA_INTERNALS_HPP
