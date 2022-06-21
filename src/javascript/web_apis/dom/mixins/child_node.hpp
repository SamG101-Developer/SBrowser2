#ifndef SBROWSER2_CHILD_NODE_HPP
#define SBROWSER2_CHILD_NODE_HPP

#include <web_apis/dom_object.hpp>
namespace dom::mixins {class child_node;}


class dom::mixins::child_node
        : public web_apis::dom_object
{
public constructors:
    child_node();

public js_methods:
    unscopable template<typename ...nodes_or_strings_t> auto before(nodes_or_strings_t&&... nodes) -> void;
    unscopable template<typename ...nodes_or_strings_t> auto after(nodes_or_strings_t&&... nodes) -> void;
    unscopable template<typename ...nodes_or_strings_t> auto replace_with(nodes_or_strings_t&&... nodes) -> void;
    unscopable auto remove() -> void;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_CHILD_NODE_HPP
