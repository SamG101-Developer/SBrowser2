#ifndef SBROWSER2_RANGE_INTERNALS_HPP
#define SBROWSER2_RANGE_INTERNALS_HPP

#include "ext/memory.ixx"

#include "ext/tuple.ixx"

#include "ext/vector.hpp"
#include <range/v3/view/any_view.hpp>
#include INCLUDE_INNER_TYPES(dom)
namespace dom::nodes {class character_data;}
namespace dom::nodes {class document_fragment;}
namespace dom::nodes {class node;}
namespace dom::node_ranges {class abstract_range;}
namespace dom::node_ranges {class range;}
namespace dom::node_ranges {class static_range;}

namespace dom::detail
{
    auto is_Valid(
            const node_ranges::static_range* range)
            -> ext::boolean;


}


#endif //SBROWSER2_RANGE_INTERNALS_HPP
