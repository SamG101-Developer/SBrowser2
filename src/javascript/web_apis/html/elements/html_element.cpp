#include "html_element.hpp"
#include "html_element_private.hpp"

#include "ext/functional.hpp"
#include "ext/ranges.hpp"

#include "dom/_typedefs.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_fragment.hpp"
#include "dom/nodes/text.hpp"
#include "dom/nodes/text_private.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/detail/tree_internals.hpp"

#include "html/detail/context_internals.hpp"
#include "html/detail/html_element_internals.hpp"
#include "html/detail/render_blocking_internals.hpp"
#include "html/other/element_internals.hpp"

#include "url/detail/url_internals.hpp"

#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/view/cache1.hpp>
#include <range/v3/view/trim.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/remove.hpp>
#include <range/v3/view/repeat.hpp>
#include <range/v3/view/replace_if.hpp>


html::elements::html_element::html_element()
{
    INIT_PIMPL(html_element);
    HTML_CONSTRUCTOR

    ACCESS_PIMPL(html_element);
    d->insertion_steps = [this] {/* TODO */ };
    d->remove_steps = [this](dom::nodes::node* parent = nullptr) {/* TODO */};
    d->activation_behaviour = [this](dom::events::event* event) {/* TODO */};
}


auto html::elements::html_element::click() -> void
{
    // TODO : return if dynamic_cast<T>(this)->disabled = True

    ACCESS_PIMPL(html_element);
    return_if (d->click_in_progress_flag);

    d->click_in_progress_flag = true;
    detail::fire_synthetic_pointer_event("click", this, true);
    d->click_in_progress_flag = false;
}


auto html::elements::html_element::attach_internals() -> other::element_internals
{
    ACCESS_PIMPL(html_element);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d] {return !d->is.empty();},
            u8"Elements 'is' value must be empty");

    decltype(auto) definition = dom::detail::lookup_custom_element_definition(d->node_document, d->namespace_, d->local_name, u8"");

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [definition] {return !definition->has_value();},
            u8"Definition must be valid");

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d] {return d->disable_internals;},
            u8"This element has disabled internals set to true");

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d] {return d->custom_element_state != PRECUSTOMIZED && d->custom_element_state != CUSTOM;},
            u8"This element must be precustomized or custom");

    d->attached_internals = true;

    auto element_internals = other::element_internals{};
    element_internals->target_element = this;
    return element_internals;
}


auto html::elements::html_element::get_title() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_element);
        return d->title;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_element::get_lang() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_element);
        return d->lang;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_element::get_translate() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_element);
        return d->translate_mode;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_element::get_dir() const -> detail::directionality_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_element);
        return d->dir;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_element::get_access_key() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_element);
        return d->access_key;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_element::get_inner_text() const -> ext::string
{
    ACCESS_PIMPL(const html_element);

    // if the HTMLElement is not being rendered at the moment, then return the descendant text content of the element;
    // the '[inner/outer]_text' property represents the data of the elements beneath this element
    return_if (!detail::being_rendered(this)) dom::detail::descendant_text_content(this);

    // define a method that converts string representations of numbers to repeated newlines of the same number; for
    // example: "2" -> "\n\n" etc
    auto map_number_to_repeated_lf =
            [](ext::string& string)
            {return ext::is_numeric_string(string) ? ext::string(std::stoll(string), char(0x000a)) : string;};

    // transform all the `child_nodes` to the result of the `rendered_text_collection_steps(...)` (vector of strings),
    // join these vectors together into the single range, remove any empty strings, convert any string-numbers to LFs
    // repeated the number of times, and finally trim newlines from the begin and end of the string
    auto results = d->child_nodes
            | ranges::views::transform(&std::unique_ptr<dom::nodes::node>::get)
            | ranges::views::transform(detail::rendered_text_collection_steps)
            | ranges::views::join
            | ranges::views::remove(u8"")
            | ranges::views::transform(map_number_to_repeated_lf)
            // TODO : | ranges::views::trim([](ext::string_view string) {return string.front() == char(0x000a);})
            ;

    return results | ranges::to<ext::string>;
}


auto html::elements::html_element::set_title(ext::string new_title) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_element);
        return d->title = std::move(new_title);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_element::set_lang(ext::string new_lang) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_element);
        return d->title = std::move(new_lang);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_element::set_translate(ext::boolean new_translate) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_element);
        return d->translate_mode = new_translate;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_element::set_dir(detail::directionality_t new_dir) -> detail::directionality_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_element);
        return d->dir = new_dir;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_element::set_access_key(ext::string new_access_key) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_element);
        return d->access_key = std::move(new_access_key);
    CE_REACTIONS_METHOD_EXE
}



auto html::elements::html_element::set_inner_text(ext::string new_inner_text) -> ext::string
{
    // to set the 'inner_text' of a HTMLElement, a DocumentFragment is generated from the input 'val', and everything
    // contained by this node is replaced with the DocumentFragment
    ACCESS_PIMPL(html_element);
    decltype(auto) fragment = detail::rendered_text_fragment(std::move(new_inner_text), d->node_document);
    dom::detail::replace_all(std::move(fragment), this);
}


auto html::elements::html_element::set_outer_text(ext::string new_outer_text) -> ext::string
{
    ACCESS_PIMPL(html_element);
    using enum dom::detail::dom_exception_error_t;

    // cannot replace the outer text if here isn't a parent node, because the outer text includes this node, which has
    // to be rooted somewhere for it to be replaced
    dom::detail::throw_v8_exception<NO_MODIFICATION_ALLOWED_ERR>(
            [d] {return !d->parent_node;},
            u8"HTML...Element must have a 'parent_node' in order to set the 'outer_text'");

    // save the current previous and next sibling nodes, which could change as a new Text node might be appended, if
    // this node's replacement doesn't have any child nodes
    decltype(auto) next = dom::detail::next_sibling(this);
    decltype(auto) prev = dom::detail::previous_sibling(this);
    decltype(auto) fragment = detail::rendered_text_fragment(std::move(new_outer_text), d->node_document);

    // if the replacement for this node doesn't have any children, then create an empty Text node, and append it to the
    // replacement 'fragment' node; the replacement has to have a child TODO : why?
    // so the default option is to add an empty Text node as the child
    if (!fragment->has_child_nodes())
    {
        auto text_node = std::make_unique<dom::nodes::text>(u8"");
        text_node->d_func()->node_document = d->node_document;
        dom::detail::append(std::move(text_node), fragment);
    }

    // replace this node with the 'fragment' in the parent node ('outer_text' replacement includes replacing this node,
    // where-as the inner text replacement replaces everything contained by this node)
    dom::detail::replace(std::move(fragment), d->parent_node, this);

    if (decltype(auto) text_node = dynamic_cast<dom::nodes::text*>(next->previous_sibling()))
        detail::merge_with_next_text_node(text_node);

    if (decltype(auto) text_node = dynamic_cast<dom::nodes::text*>(prev))
        detail::merge_with_next_text_node(text_node);
}


auto html::elements::html_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_element>{isolate}
        .inherit<dom::nodes::element>()
        .inherit<mixins::content_editable>()
        .inherit<mixins::html_or_svg_element>()
        .inherit<css::cssom::mixins::element_css_inline_style>()
        .auto_wrap_objects(); // TODO
}
