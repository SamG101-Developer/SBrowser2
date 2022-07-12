#include "html_element.hpp"

#include "ext/functional.hpp"
#include "ext/ranges.hpp"

#include "dom/nodes/document.hpp"
#include "dom/nodes/document_fragment.hpp"
#include "dom/nodes/text.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/detail/tree_internals.hpp"

#include "html/detail/html_element_internals.hpp"
#include "html/detail/render_blocking_internals.hpp"

#include <range/v3/view/cache1.hpp>
#include <range/v3/view/trim.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/remove.hpp>
#include <range/v3/view/repeat.hpp>
#include <range/v3/view/replace_if.hpp>


html::elements::html_element::html_element()
{
    bind_get(inner_text);
    bind_get(outer_text);

    bind_set(inner_text);
    bind_set(outer_text);

    HTML_CONSTRUCTOR
}


auto html::elements::html_element::get_inner_text()
        const -> ext::string
{
    // if the HTMLElement is not being rendered at the moment, then return the descendant text content of the element;
    // the '[inner/outer]_text' property represents the data of the elements beneath this element
    return_if (!detail::render_blocking_internals::being_rendered(this)) dom::detail::tree_internals::descendant_text_content(this);

    // define a method that converts string representations of numbers to repeated newlines of the same number; for
    // example: "2" -> "\n\n" etc
    auto map_number_to_repeated_lf = [](ext::string& string)
    {
        return ext::is_numeric_string(string) ? ext::string(std::stoll(string), char(0x000a)) : string;
    };

    // transform all the `child_nodes` to the result of the `rendered_text_collection_steps(...)` (vector of strings),
    // join these vectors together into the single range, remove any empty strings, convert any string-numbers to LFs
    // repeated the number of times, and finally trim newlines from the begin and end of the string
    auto results = *child_nodes()
            | ranges::views::transform(detail::html_element_internals::rendered_text_collection_steps)
            | ranges::views::join
            | ranges::views::remove("")
            | ranges::views::transform(map_number_to_repeated_lf)
            // TODO : | ranges::views::trim([](ext::string_view string) {return string.front() == char(0x000a);})
            ;

    return results | ranges::to<ext::string>;
}


auto html::elements::html_element::set_inner_text(
        ext::string_view val)
        -> void
{
    // to set the 'inner_text' of a HTMLElement, a DocumentFragment is generated from the input 'val', and everything
    // contained by this node is replaced with the DocumentFragment
    auto* fragment = detail::html_element_internals::rendered_text_fragment(val, owner_document());
    dom::detail::mutation_internals::replace_all(fragment, this);
}


auto html::elements::html_element::set_outer_text(
        ext::string_view val)
        -> void
{
    // cannot replace the outer text if here isn't a parent node, because the outer text includes this node, which has
    // to be rooted somewhere for it to be replaced
    dom::detail::exception_internals::throw_v8_exception_formatted<NO_MODIFICATION_ALLOWED_ERR>(
            [this] {return !parent_node();},
            "HTMLxxxElement must have a 'parent_node' in order to set the 'outer_text'");

    // save the current previous and next sibling nodes, which could change as a new Text node might be appended, if
    // this node's replacement doesn't have any child nodes
    auto* next = next_sibling();
    auto* prev = previous_sibling();
    auto* fragment = detail::html_element_internals::rendered_text_fragment(val, owner_document());

    // if the replacement for this node doesn't have any children, then create an empty Text node, and append it to the
    // replacement 'fragment' node; the replacement has to have a child TODO : why?
    // so the default option is to add an empty Text node as the child
    if (!fragment->has_child_nodes())
    {
        dom::nodes::text text_node {""};
        text_node.owner_document = owner_document();
        dom::detail::mutation_internals::append(&text_node, fragment);
    }

    // replace this node with the 'fragment' in the parent node ('outer_text' replacement includes replacing this node,
    // where-as the inner text replacement replaces everything contained by this node)
    dom::detail::mutation_internals::replace(fragment, parent_node(), this);

    if (auto* text_node = dynamic_cast<dom::nodes::text*>(next->previous_sibling()))
        detail::html_element_internals::merge_with_next_text_node(text_node);

    if (auto* text_node = dynamic_cast<dom::nodes::text*>(prev))
        detail::html_element_internals::merge_with_next_text_node(text_node);
}
