#ifndef SBROWSER2_PARENTABLE_NODE_HPP
#define SBROWSER2_PARENTABLE_NODE_HPP

#include "dom_object.hpp"
namespace dom::mixins {class parentable_node;}

#include "ext/vector.hpp"
#include "ext/type_traits.hpp"

#include <range/v3/view/any_view.hpp>
namespace dom::nodes {class element;}
namespace dom::nodes {class node;}


class dom::mixins::parentable_node
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(parentable_node);
    parentable_node();

public js_methods:
    unscopable template <type_is<nodes::node*, ext::string> ...T> auto prepend(T&&... nodes) -> nodes::node*;
    unscopable template <type_is<nodes::node*, ext::string> ...T> auto append(T&&... nodes) -> nodes::node*;
    unscopable template <type_is<nodes::node*, ext::string> ...T> auto replace_children(T&&... nodes) -> nodes::node*;

    auto query_selector(ext::string_view selectors);
    auto query_selector_all(ext::string_view selectors);

public js_properties:
    ext::property<ranges::any_view<nodes::element*, ranges::category::sized | ranges::category::forward>> children;
    ext::property<nodes::element*> first_element_child;
    ext::property<nodes::element*> last_element_child;
    ext::property<size_t> child_element_count;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    [[nodiscard]] auto get_children() const -> ranges::any_view<nodes::element*, ranges::category::sized | ranges::category::forward>;
    [[nodiscard]] auto get_first_element_child() const -> nodes::element*;
    [[nodiscard]] auto get_last_element_child() const -> nodes::element*;
    [[nodiscard]] auto get_child_element_count() const -> size_t;
};


#endif //SBROWSER2_PARENTABLE_NODE_HPP
