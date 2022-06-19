#ifndef SBROWSER2_ABSTRACT_RANGE_HPP
#define SBROWSER2_ABSTRACT_RANGE_HPP

#include <web_apis/dom_object.hpp>
namespace dom::node_ranges {class abstract_range;}

namespace dom::nodes {class node;}


class dom::node_ranges::abstract_range
        : public virtual web_apis::dom_object
{
public constructors:
    using web_apis::dom_object::dom_object;

public js_properties:
    ext::property<ext::boolean> collapsed;
    ext::property<std::unique_ptr<nodes::node>> start_container;
    ext::property<std::unique_ptr<nodes::node>> end_container;
    ext::property<ext::number<ulong>> start_offset;
    ext::property<ext::number<ulong>> end_offset;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_ABSTRACT_RANGE_HPP
