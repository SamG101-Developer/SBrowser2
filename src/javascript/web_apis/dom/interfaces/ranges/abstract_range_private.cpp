module apis.dom.abstract_range:p;

import ext.core;


auto dom::abstract_range_private::is_range_collapsed() const -> ext::boolean
{
    return start->node.get() == end->node.get() && start->offset == end->offset;
}
