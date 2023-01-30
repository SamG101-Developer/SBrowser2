module;
#include "ext/macros/custom_operator.hpp"
#include "ext/macros.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/range/operations.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/for_each.hpp>


module apis.dom.document;
import apis.dom.event;
import apis.dom.window;

import js.env.realms;
import ext.core;


dom::document::document()
{
    INIT_PIMPL; ACCESS_PIMPL;

    auto e = js::env::env::surrounding(this);
    d->url = std::make_unique<url::detail::url_t>(u"about:blank");
    d->content_type = u"application/xml";
    d->ready_state = u"complete";
    d->origin = e.cpp.settings()->origin; // TODO : settings?
    d->get_the_parent =
            [this, d](event* event)
            {
                auto e = js::env::env::relevant(this);
                return_if(event->d_func()->type == u"load" || !d->browsing_context) ext::nullptr_cast<event_target*>();

                decltype(auto) global_object = e.cpp.global<window*>();
                return global_object;
            };

    permissions_policy()->m_associated_node = this;
}


auto dom::document::create_element(
        ext::string&& local_name,
        ext::map<ext::string, ext::any>&& options)
        -> std::unique_ptr<element>
{
    _CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const document);

        // create the html adjusted local name and namespace, and get the 'is' option from the options dictionary - set it
        // to the empty string otherwise
        auto html_adjusted_local_name = detail::html_adjust_string(std::move(local_name), d->type == u"html");
        auto html_adjusted_namespace_ = d->type == u"html" || d->content_type == u"application/xhtml+xml" ? detail::HTML : u"";
        auto is = options[u"is"].to<ext::string>();

        // create the Element node with the html adjusted variables
        return detail::create_an_element(this, html_adjusted_local_name, html_adjusted_namespace_, u8"", is, true);
    _CE_REACTIONS_METHOD_EXE
}


auto dom::document::create_element_ns(
        ext::string&& namespace_,
        ext::string&& qualified_name,
        ext::map<ext::string, ext::any>&& options)
        -> std::unique_ptr<element>
{
    CE_REACTIONS_METHOD_DEF
        // determine the 'prefix' and 'local_name' from the 'namespace_' and 'qualified_name', using the detail
        // 'validate_and_extract(...)' method
        auto [prefix, local_name] = detail::validate_and_extract(std::move(namespace_), std::move(qualified_name));
        auto is = options[u"is"].to<ext::string>();

        // create the Element node with the html adjusted variables
        return detail::create_an_element(this, local_name, std::move(namespace_), prefix, is, true);
    CE_REACTIONS_METHOD_EXE
}


auto dom::document::create_document_fragment() -> std::unique_ptr<document_fragment>
{
    // create a DocumentFragment node, and set its owner document to this document
    auto node = std::make_unique<document_fragment>();
    node->d_func()->node_document = this;
    return node;
}


auto dom::document::create_text_node(ext::string&& data) -> std::unique_ptr<text>
{
    // create a Text node, and set its data and owner document to the 'data' parameter and this document
    auto node = std::make_unique<text>();
    node->d_func()->data = std::move(data);
    node->d_func()->node_document = this;
    return node;
}


auto dom::document::create_cdata_section_node(ext::string&& data) -> std::unique_ptr<cdata_section>
{
    ACCESS_PIMPL(const document);
    using enum detail::dom_exception_error_t;

    detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
            [this, type = d->type] {return type == u"html";},
            u8"Cannot create a CDataSection node in a HTML Document");

    detail::throw_v8_exception<INVALID_CHARACTER_ERR>(
            [data = std::move(data)] {return data.contains(u"]]>");},
            u8"Cannot create a CDataSection node with ']]>' in the data");

    auto node = std::make_unique<cdata_section>();
    node->d_func()->data = std::move(data);
    node->d_func()->node_document = const_cast<document*>(this);
    return node;
}


auto dom::document::create_comment(ext::string&& data) -> std::unique_ptr<comment>
{
    auto node = std::make_unique<comment>();
    node.d_func()->data = std::move(data);
    node.d_func()->node_document = const_cast<document*>(this);
    return node;
}


auto dom::document::create_processing_instruction(ext::string&& target, ext::string&& data) -> std::unique_ptr<processing_instruction>
{
    using enum detail::dom_exception_error_t;

    detail::throw_v8_exception<INVALID_CHARACTER_ERR>(
            [data = std::move(data)] {return data.contains(u"?>");},
            u8"Cannot create a CDataSection node with '?>' in the data");

    auto node = std::make_unique<processing_instruction>();
    node->d_func()->data = std::move(data);
    node->d_func()->target = std::move(target);
    node->d_func()->node_document = const_cast<document*>(this);
    return node;
}


auto dom::document::create_attribute(ext::string&& local_name) -> std::unique_ptr<attr>
{
    ACCESS_PIMPL(const document);
    auto html_adjusted_local_name = d->type == u"html"
            ? local_name | ranges::views::lowercase | ranges::to<ext::string>
            : std::move(local_name);

    auto node = std::unique_ptr<attr>();
    node->d_func()->local_name = html_adjusted_local_name;
    node->d_func()->node_document = const_cast<document*>(this);
    return node;
}


auto dom::document::create_attribute_ns(ext::string&& namespace_, ext::string&& qualified_name) -> std::unique_ptr<attr>
{
    auto [prefix, local_name] = detail::validate_and_extract(std::move(namespace_), std::move(qualified_name));

    auto node = std::make_unique<attr>();
    node->d_func()->local_name = std::move(local_name);
    node->d_func()->namespace_prefix = std::move(prefix);
    node->d_func()->namespace_ = std::move(namespace_);
    node->d_func()->node_document = const_cast<document*>(this);
    return node;
}


auto dom::document::create_range() -> std::unique_ptr<node_ranges::range>
{
    auto live_range = std::unique_ptr<node_ranges::range>();

    ext::tie(live_range->d_func()->start->node, live_range.d_func()->start->offset) = ext::make_tuple(this, 0);
    ext::tie(live_range->d_func()->end->node, live_range->d_func()->end->offset) = ext::make_tuple(this, 0);
    return live_range;
}


auto dom::document::import_node(node* new_node, ext::boolean deep) -> node*
{
    using enum detail::dom_exception_error_t;

    CE_REACTIONS_METHOD_DEF
        detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
                [new_node] {return ext::multi_cast<nodes::document*, nodes::shadow_root*>(new_node);},
                u8"Node being imported cannot be a Document or ShadowRoot");

        // to import a node, a clone of the node is made, with the Document set tot this node; the node is basically copied
        // into this Document
        return detail::clone(new_node, this, true);
    CE_REACTIONS_METHOD_EXE
}


auto dom::document::adopt_node(node* new_node) -> node*
{
    using enum detail::dom_exception_error_t;

    CE_REACTIONS_METHOD_DEF
        detail::throw_v8_exception<NOT_SUPPORTED_ERR>(
                [new_node] {return ext::multi_cast<nodes::document*>(new_node);},
                u8"Node being imported cannot be a Document");

        detail::throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                [new_node] {return ext::multi_cast<nodes::shadow_root*>(new_node);},
                u8"Node being imported cannot be a ShadowRoot");

        // to adopt a node, the node is moved, not copied, from its current Document node to this Document Node; no cloning
        // takes place
        return detail::adopt(new_node, this);
    CE_REACTIONS_METHOD_EXE
}


auto dom::document::set_visibility_state(page_visibility::detail::visibility_state_t new_visibility_state) -> page_visibility::detail::visibility_state_t
{
    ACCESS_PIMPL(document);

    /* [SCREEN-WAKE-LOCK] */
    return_if (new_visibility_state != page_visibility::detail::visibility_state_t::HIDDEN) new_visibility_state;
    d->acive_locks.at(screen_wake_lock::detail::SCRREN) | ranges::views::for_each(BIND_FRONT(&screen_wake_lock::detail::release_wake_lock, screen_wake_lock::detail::SCRREN, this));
}


auto dom::document::operator[](
        const ext::string& name)
        -> ranges::any_view<element*>&
{
    // return all descendant element in this tree whose name attribute (only present on certain element interfaces) is
    // equal to the 'name' parameter; TODO: named_element concept with property `name` -> cast all, filter, and cast back
    return detail::descendants(this)
            | ranges::views::filter([name](element* descendant) {return descendant->name() == name;});
}


auto dom::document::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<node>()
        .inherit<mixins::document_or_element_node>()
        .inherit<mixins::document_or_shadow_root>()
        .inherit<mixins::non_element_parent_node>()
        .inherit<mixins::parentable_node>()
        .inherit<xpath::xpath_evaluator_base>()
        .inherit<ext::map_like<ext::string, ranges::any_view<element*>>>()
        .function("createElement", &document::create_element)
        .function("createElementNS", &document::create_element_ns)
        .function("createDocumentFragment", &document::create_document_fragment)
        .function("createTextNode", &document::create_text_node)
        .function("createCDataSectionNode", &document::create_cdata_section_node)
        .function("createComment", &document::create_comment)
        .function("createProcessingInstruction", &document::create_processing_instruction)
        .function("createAttribute", &document::create_attribute)
        .function("createAttributeNS", &document::create_attribute_ns)
        .function("createRange", &document::create_range)
        .function("createNodeIterator", &document::create_node_iterator)
        .function("createTreeWalker", &document::create_tree_walker)
        .function("importNode", &document::import_node)
        .function("adoptNode", &document::adopt_node)
        .property("nodeType", &document::get_node_type)
        .property("nodeName", &document::get_node_name)
        .property("nodeValue", &document::get_node_value, &document::set_node_value)
        .property("textContent", &document::get_text_content, &document::set_text_content)
        .property("url", &document::get_url)
        .property("compatMode", &document::get_compat_mode)
        .property("characterSet", &document::get_character_set)
        .property("contentType", &document::get_content_type)
        .property("doctype", &document::get_doctype)
        .property("documentElement", &document::get_document_element)
        .property("implementation", &document::get_implementation)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
