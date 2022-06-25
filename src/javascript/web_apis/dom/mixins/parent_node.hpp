#ifndef SBROWSER2_PARENT_NODE_HPP
#define SBROWSER2_PARENT_NODE_HPP

#include <ext/vector.hpp>
#include <ext/type_traits.hpp>
#include <web_apis/dom_object.hpp>
#include <range/v3/view/ref.hpp>
namespace dom::mixins {class parent_node;}
namespace dom::nodes {class element;}


class dom::mixins::parent_node
        : public virtual web_apis::dom_object
{
public constructors:
    parent_node();

public js_methods:
    unscopable auto prepend(same_as_any<nodes::node*, ext::string> auto&&... nodes) -> void;
    unscopable auto append(same_as_any<nodes::node*, ext::string> auto&&... nodes) -> void;
    unscopable auto replace_children(same_as_any<nodes::node*, ext::string> auto&&... nodes) -> void;

    auto query_selector(ext::string_view selectors);
    auto query_selector_all(ext::string_view selectors);

public js_properties:
    ext::property<ranges::ref_view<ext::vector<nodes::element*>>> children;
    ext::property<nodes::element*> first_element_child;
    ext::property<nodes::element*> last_element_child;
    ext::property<size_t> child_element_count;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_accessors:
    [[nodiscard]] auto get_children() const -> ranges::ref_view<ext::vector<nodes::element*>>;
    [[nodiscard]] auto get_first_element_child() const -> nodes::element* {return children->front();};
    [[nodiscard]] auto get_last_element_child() const -> nodes::element* {return children->back();};
    [[nodiscard]] auto get_child_element_count() const -> size_t {return children->size();};
};


#endif //SBROWSER2_PARENT_NODE_HPP
