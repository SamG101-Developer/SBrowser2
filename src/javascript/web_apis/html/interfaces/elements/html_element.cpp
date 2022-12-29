module;
#include "ext/macros/custom_operator.hpp"
#include "ext/macros/language_shorthand.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include "javascript/macros/errors.hpp"
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/view/cache1.hpp>
#include <range/v3/view/trim.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/remove.hpp>
#include <range/v3/view/repeat.hpp>
#include <range/v3/view/replace_if.hpp>


module apis.html.html_element;
import apis.html.html_element_private;
import apis.html.detail;
import apis.html.types;

import apis.dom.event;
import apis.dom.element;
import apis.dom.node;
import apis.dom.detail;
import apis.dom.types;

import ext.core;
import js.env.realms;
import js.env.module_type;


html::html_element::html_element()
{
    INIT_PIMPL; ACCESS_PIMPL;
    _HTML_CONSTRUCTOR

    d->insertion_steps = [this] {/* TODO */ };
    d->remove_steps = [this](dom::node* parent = nullptr) {/* TODO */};
    d->activation_behaviour = [this](dom::event* event) {/* TODO */};
}


auto html::html_element::click() -> void
{
    // TODO : return if dynamic_cast<T>(this)->disabled = True

    ACCESS_PIMPL;
    return_if (d->click_in_progress_flag);

    d->click_in_progress_flag = true;
    detail::fire_synthetic_pointer_event(u"click", this, true);
    d->click_in_progress_flag = false;
}


auto html::html_element::attach_internals() -> std::unique_ptr<element_internals>
{
    ACCESS_PIMPL;
    using enum dom::detail::dom_exception_error_t;
    auto e = js::env::env::relevant(this);
    

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d] {return !d->is.empty();},
            u8"Elements 'is' value must be empty", e);

    decltype(auto) definition = dom::detail::lookup_custom_element_definition(d->node_document.get(), d->namespace_, d->local_name, u8"");

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [definition] {return !definition->has_value();},
            u8"Definition must be valid", e);

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d] {return d->disable_internals;},
            u8"This element has disabled internals set to true", e);

    dom::detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [d] {return d->custom_element_state != PRECUSTOMIZED && d->custom_element_state != CUSTOM;},
            u8"This element must be precustomized or custom", e);

    d->attached_internals = true;

    auto element_internals = std::make_unique<element_internals>();
    element_internals->d_func()->target_element = this;
    return element_internals;
}


auto html::html_element::get_title() const -> ext::string_view
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->title;
    _CE_REACTIONS_METHOD_EXE
}


auto html::html_element::get_lang() const -> ext::string_view
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->lang;
    _CE_REACTIONS_METHOD_EXE
}


auto html::html_element::get_translate() const -> ext::boolean
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->translate_mode;
    _CE_REACTIONS_METHOD_EXE
}


auto html::html_element::get_dir() const -> detail::directionality_t
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->dir;
    _CE_REACTIONS_METHOD_EXE
}


auto html::html_element::get_access_key() const -> ext::string_view
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->access_key;
    _CE_REACTIONS_METHOD_EXE
}


auto html::html_element::get_inner_text() const -> ext::string
{
    ACCESS_PIMPL;

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


auto html::html_element::set_title(ext::string new_title) -> ext::string
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->title = std::move(new_title);
    _CE_REACTIONS_METHOD_EXE
}


auto html::html_element::set_lang(ext::string new_lang) -> ext::string
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->title = std::move(new_lang);
    _CE_REACTIONS_METHOD_EXE
}


auto html::html_element::set_translate(ext::boolean new_translate) -> ext::boolean
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->translate_mode = new_translate;
    _CE_REACTIONS_METHOD_EXE
}


auto html::html_element::set_dir(detail::directionality_t new_dir) -> detail::directionality_t
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->dir = new_dir;
    _CE_REACTIONS_METHOD_EXE
}


auto html::html_element::set_access_key(ext::string new_access_key) -> ext::string
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL;
        return d->access_key = std::move(new_access_key);
    _CE_REACTIONS_METHOD_EXE
}



auto html::html_element::set_inner_text(ext::string new_inner_text) -> ext::string
{
    // to set the 'inner_text' of a HTMLElement, a DocumentFragment is generated from the input 'val', and everything
    // contained by this node is replaced with the DocumentFragment
    ACCESS_PIMPL;
    decltype(auto) fragment = detail::rendered_text_fragment(std::move(new_inner_text), d->node_document.get());
    dom::detail::replace_all(std::move(fragment), this);
}


auto html::html_element::set_outer_text(ext::string new_outer_text) -> ext::string
{
    ACCESS_PIMPL;
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
    decltype(auto) fragment = detail::rendered_text_fragment(std::move(new_outer_text), d->node_document.get());

    // if the replacement for this node doesn't have any children, then create an empty Text node, and append it to the
    // replacement 'fragment' node; the replacement has to have a child TODO : why?
    // so the default option is to add an empty Text node as the child
    if (!fragment->has_child_nodes())
    {
        auto text_node = std::make_unique<dom::nodes::text>(u"");
        text_node->d_func()->node_document = d->node_document.get();
        dom::detail::append(std::move(text_node), fragment.get());
    }

    // replace this node with the 'fragment' in the parent node ('outer_text' replacement includes replacing this node,
    // where-as the inner text replacement replaces everything contained by this node)
    dom::detail::replace(std::move(fragment), d->parent_node.get(), this);

    if (decltype(auto) text_node = dynamic_cast<dom::nodes::text*>(dom::detail::previous_sibling(next)))
        detail::merge_with_next_text_node(text_node);

    if (decltype(auto) text_node = dynamic_cast<dom::nodes::text*>(prev))
        detail::merge_with_next_text_node(text_node);
}


auto html::html_element::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::element>()
        .inherit<content_editable>()
        .inherit<html_or_svg_element>()
        .function("click", &html_element::click)
        .function("attachInternals", &html_element::attach_internals)
        .property("title", &html_element::get_title, &html_element::set_title)
        .property("lang", &html_element::get_lang, &html_element::set_lang)
        .property("translate", &html_element::get_translate, &html_element::set_translate)
        .property("dir", &html_element::get_title, &html_element::set_title)
        .property("hidden", &html_element::get_hidden, &html_element::set_hidden)
        .property("inert", &html_element::get_inert, &html_element::set_inert)
        .property("accessKey", &html_element::get_access_key, &html_element::set_access_key)
        .property("accessKeyLabel", &html_element::get_access_key_label)
        .property("draggable", &html_element::get_draggable, &html_element::set_draggable)
        .property("spellcheck", &html_element::get_spellcheck, &html_element::set_spellcheck)
        .property("autocapitalize", &html_element::get_autocapitalize, &html_element::set_autocapitalize)
        .property("innerText", &html_element::get_inner_text, &html_element::set_inner_text)
        .property("outerText", &html_element::get_outer_text, &html_element::set_outer_text)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
