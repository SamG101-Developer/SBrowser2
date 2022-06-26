#ifndef SBROWSER2_CHILD_NODE_HPP
#define SBROWSER2_CHILD_NODE_HPP

#include <web_apis/dom_object.hpp>
namespace dom::mixins {class child_node;}


class dom::mixins::child_node
        : public virtual web_apis::dom_object
{
public constructors:
    child_node();

public js_methods:
    unscopable auto before(same_as_any<nodes::node*, ext::string> auto&&... nodes) -> void;
    unscopable auto after(same_as_any<nodes::node*, ext::string> auto&&... nodes) -> void;
    unscopable auto replace_with(same_as_any<nodes::node*, ext::string> auto&&... nodes) -> void;
    unscopable auto remove() -> void;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_CHILD_NODE_HPP
