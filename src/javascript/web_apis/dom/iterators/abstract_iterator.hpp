#pragma once
#ifndef SBROWSER2_ABSTRACT_ITERATOR_HPP
#define SBROWSER2_ABSTRACT_ITERATOR_HPP

#include "dom_object.hpp"
namespace dom::node_iterators {class abstract_iterator;}

namespace dom::node_iterators {class node_filter;}
namespace dom::nodes {class node;}


class dom::node_iterators::abstract_iterator
        : public virtual web_apis::dom_object
{
public constructors:
    abstract_iterator();

public js_properties:
    ext::property<std::unique_ptr<node_filter>> filter;
    ext::property<std::unique_ptr<nodes::node>> root;
    ext::property<ext::number<ulong>> what_to_show;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    ext::boolean m_active_flag;
};


#endif //SBROWSER2_ABSTRACT_ITERATOR_HPP
