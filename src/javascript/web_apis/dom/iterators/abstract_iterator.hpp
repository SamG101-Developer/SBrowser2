#pragma once
#ifndef SBROWSER2_ABSTRACT_ITERATOR_HPP
#define SBROWSER2_ABSTRACT_ITERATOR_HPP

#include "dom_object.hpp"
namespace dom::node_iterators {class abstract_iterator;}

namespace dom::node_iterators {class node_filter;}
namespace dom::nodes {class node;}

namespace dom::detail {auto filter(const nodes::node*, node_iterators::abstract_iterator*) -> ext::number<ushort>;}


class dom::node_iterators::abstract_iterator
        : public virtual dom_object
{
public friends:
    friend auto dom::detail::filter(
            const nodes::node* node, node_iterators::abstract_iterator* iterator) -> ext::number<ushort>;

public constructors:
    DOM_CTORS(abstract_iterator);
    abstract_iterator();

public js_properties:
    ext::property<std::unique_ptr<node_filter>> filter;
    ext::property<std::unique_ptr<nodes::node>> root;
    ext::property<ext::number<ulong>> what_to_show;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_properties:
    ext::boolean m_active_flag;
};


#endif //SBROWSER2_ABSTRACT_ITERATOR_HPP
