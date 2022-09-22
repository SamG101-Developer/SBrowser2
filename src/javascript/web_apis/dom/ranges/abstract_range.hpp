#ifndef SBROWSER2_ABSTRACT_RANGE_HPP
#define SBROWSER2_ABSTRACT_RANGE_HPP

#include "dom_object.hpp"
namespace dom::node_ranges {class abstract_range;}

namespace dom::nodes {class node;}

#include "dom/ranges/abstract_range_private.hpp"


class dom::node_ranges::abstract_range
        : public virtual dom_object
{
public constructors:
    abstract_range() = default;

public js_properties:
    ext::property<nodes::node*> start_container;
    ext::property<nodes::node*> end_container;
    ext::property<ext::number<ulong>> start_offset;
    ext::property<ext::number<ulong>> end_offset;
    ext::property<ext::boolean> collapsed;

public cpp_members:
    MAKE_PIMPL(abstract_range);
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(start_container);
    DEFINE_CUSTOM_GETTER(end_container);
    DEFINE_CUSTOM_GETTER(start_offset);
    DEFINE_CUSTOM_GETTER(end_offset);
    DEFINE_CUSTOM_GETTER(collapsed);
};


#endif //SBROWSER2_ABSTRACT_RANGE_HPP
