#ifndef SBROWSER2_ABSTRACT_RANGE_HPP
#define SBROWSER2_ABSTRACT_RANGE_HPP

#include "dom_object.hpp"
namespace dom::node_ranges {class abstract_range;}
namespace dom::node_ranges {class abstract_range_private;}

namespace dom::nodes {class node;}


class dom::node_ranges::abstract_range
        : public virtual dom_object
{
public constructors:
    abstract_range();
    MAKE_PIMPL(abstract_range);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(start_container, nodes::node*);
    DEFINE_GETTER(start_offset, ext::number<ulong>);
    DEFINE_GETTER(end_container, nodes::node*);
    DEFINE_GETTER(end_offset, ext::number<ulong>);
    DEFINE_GETTER(collapsed, ext::boolean);
};


#endif //SBROWSER2_ABSTRACT_RANGE_HPP
