#include "document.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/detail/tree_internals.hpp"

#include "ext/casting.hpp"
#include "ext/ranges.hpp"
#include "javascript/environment/realms_2.hpp"

#include "dom/detail/event_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/detail/namespace_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/nodes/attr.hpp"
#include "dom/nodes/cdata_section.hpp"
#include "dom/nodes/comment.hpp"
#include "dom/nodes/document_fragment.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/processing_instruction.hpp"
#include "dom/nodes/shadow_root.hpp"
#include "dom/other/dom_implementation.hpp"
#include "dom/ranges/range.hpp"

#include "html/detail/document_internals.hpp"
#include "html/elements/html_body_element.hpp"
#include "html/elements/html_head_element.hpp"
#include "html/elements/html_html_element.hpp"
#include "html/elements/html_script_element.hpp"
#include "html/elements/html_title_element.hpp"

#include "high_resolution_time/detail/time_internals.hpp"
#include "infra/detail/infra_strings_internals.hpp"
#include "svg/elements/svg_title_element.hpp"
#include "url/url.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>
#include <variant>

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/range/operations.hpp>
#include <range/v3/view/filter.hpp>

#include <QtCore/QPointer>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollArea>


dom::nodes::document::document()
        : url{std::make_unique<url::url_object>("about:blank")}
        , implementation{std::make_unique<other::dom_implementation>()}
        , content_type{"application/xml"}
        , ready_state{"complete"}
        , current_script{nullptr}
{
    bind_get(compat_mode);
    bind_get(character_set);
    bind_get(doctype);
    bind_get(document_element);

    bind_get(last_modified);
    bind_get(cookie);
    bind_get(body);
    bind_get(head);
    bind_get(title);
    bind_get(images);
    bind_get(links);
    bind_get(forms);
    bind_get(scripts);
    bind_get(dir);

    bind_set(ready_state);
    bind_set(cookie);
    bind_set(title);
    bind_set(body);

    JS_REALM_GET_SURROUNDING(this)
    m_origin = javascript::environment::realms_2::get<ext::string>(this_surrounding_global_object, "origin");

    auto rendered_widget = QPointer<QScrollArea>{};
    rendered_widget->setWidget(QPointer<QWidget>{});
    rendered_widget->widget()->setLayout(QPointer<QVBoxLayout>{});
    rendered_widget->setWidgetResizable(true);
    m_rendered_widget = rendered_widget;
}


auto dom::nodes::document::create_element(
        ext::string_view local_name,
        ext::string_any_map_view options)
        const -> element
{
    ce_reactions_method_def
        // create the html adjusted local name and namespace, and get the 'is' option from the options dictionary - set it
        // to the empty string otherwise
        auto html_adjusted_local_name = detail::namespace_internals::html_adjust_string(local_name, m_type == "html");
        auto html_adjusted_namespace_ = m_type == "html" || content_type() == "application/xhtml+xml" ? detail::namespace_internals::HTML : "";
        auto is = options.at("is").value_to_or<ext::string>("");

        // create the Element node with the html adjusted variables
        return detail::customization_internals::create_an_element(this, html_adjusted_local_name, html_adjusted_namespace_, "", is, true);
    ce_reactions_method_exe
}


auto dom::nodes::document::create_element_ns(
        ext::string_view namespace_,
        ext::string_view qualified_name,
        ext::string_any_map_view options)
        const -> element
{
    ce_reactions_method_def
        // determine the 'prefix' and 'local_name' from the 'namespace_' and 'qualified_name', using the detail
        // 'validate_and_extract(...)' method
        auto [prefix, local_name] = detail::namespace_internals::validate_and_extract(namespace_, qualified_name);
        auto is = options.at("is").value_to_or<ext::string>("");

        // create the Element node with the html adjusted variables
        return detail::customization_internals::create_an_element(this, local_name, namespace_, prefix, is, true);
    ce_reactions_method_exe
}


auto dom::nodes::document::create_document_fragment()
        const -> document_fragment
{
    // create a DocumentFragment node, and set its owner document to this document
    document_fragment node;
    node.owner_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_text_node(
        ext::string_view data)
        const -> text
{
    // create a Text node, and set its data and owner document to the 'data' parameter and this document
    text node;
    node.data = data;
    node.owner_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_cdata_section_node(
        ext::string_view data)
        const -> cdata_section
{
    detail::exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
            [this] {return m_type == "html";},
            "Cannot create a CDataSection node in a HTML Document");

    detail::exception_internals::throw_v8_exception_formatted<INVALID_CHARACTER_ERR>(
            [data] {return ranges::contains(data, "]]>");},
            "Cannot create a CDataSection node with ']]>' in the data");

    cdata_section node;
    node.data = data;
    node.owner_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_comment(
        ext::string_view data)
        const -> comment
{
    comment node;
    node.data = data;
    node.owner_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_processing_instruction(
        ext::string_view target,
        ext::string_view data)
        const -> processing_instruction
{
    detail::exception_internals::throw_v8_exception_formatted<INVALID_CHARACTER_ERR>(
            [data] {return ranges::contains(data, "?>");},
            "Cannot create a CDataSection node with '?>' in the data");

    processing_instruction node;
    node.data = data;
    node.target = target;
    node.owner_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_attribute(
        ext::string_view local_name)
        const -> attr
{
    auto html_adjusted_local_name = m_type == "html" ? local_name | ranges::views::lowercase() : local_name;

    attr node;
    node.local_name = html_adjusted_local_name;
    node.owner_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_attribute_ns(
        ext::string_view namespace_,
        ext::string_view qualified_name)
        const -> attr
{
    auto [prefix, local_name] = detail::namespace_internals::validate_and_extract(namespace_, qualified_name);

    attr node;
    node.local_name = std::move(local_name);
    node.prefix = std::move(prefix);
    node.namespace_uri = namespace_;
    node.owner_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_range()
        const -> node_ranges::range
{
    node_ranges::range live_range;

    std::tie(live_range.start_container, live_range.start_offset) = std::make_tuple(const_cast<document*>(this), 0);
    std::tie(live_range.end_container, live_range.end_offset) = std::make_tuple(const_cast<document*>(this), 0);
    return live_range;
}


auto dom::nodes::document::import_node(
        node* new_node,
        ext::boolean_view deep)
        -> node*
{
    ce_reactions_method_def
        detail::exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
                [new_node] {return ext::multi_cast<nodes::document*, nodes::shadow_root*>(new_node);},
                "Node being imported cannot be a Document or ShadowRoot");

        // to import a node, a clone of the node is made, with the Document set tot this node; the node is basically copied
        // into this Document
        return detail::node_internals::clone(new_node, this, true);
    ce_reactions_method_exe
}


auto dom::nodes::document::adopt_node(
        node* new_node)
        -> node*
{
    ce_reactions_method_def
        detail::exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
                [new_node] {return ext::multi_cast<nodes::document*>(new_node);},
                "Node being imported cannot be a Document");

        detail::exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                [new_node] {return ext::multi_cast<nodes::shadow_root*>(new_node);},
                "Node being imported cannot be a ShadowRoot");

        // to adopt a node, the node is moved, not copied, from its current Document node to this Document Node; no cloning
        // takes place
        return detail::node_internals::adopt(new_node, this);
    ce_reactions_method_exe
}


auto dom::nodes::document::get_last_modified()
        const -> ext::string
{
    // get the string epoch time (eg "1563566272"), and convert it to a 'long long' number type. convert this into a c++
    // time object with a strict format, push this into a stream, and finally return the string that the
    // std::stringstream holds
    std::time_t decimal_time = std::stoll(*last_modified);
    auto formatted_time = std::stringstream{} << std::put_time(std::localtime(&decimal_time), "%m/%d/%Y %H:%M:%S");
    return formatted_time.str();
}


auto dom::nodes::document::get_cookie()
        const -> ext::string
{
    // if this Document is cookie averse, then it is not in the correct condition to return the value of the cookie, so
    // return the empty string instead.
    return_if (html::detail::document_internals::is_cookie_averse_document(this)) "";

    // if the origin of this Document is opaque, then throw a security error, because the security of the cookie cannot
    // be guaranteed, despite the Document not being cookie averse
    detail::exception_internals::throw_v8_exception_formatted<SECURITY_ERR>(
            [this] {return m_origin.is_opaque();},
            "Can not get the cookie of a Document whose origin is opaque");

    // return the true value of the cookie
    return *cookie;
}


auto dom::nodes::document::get_head()
        const -> html::elements::html_head_element*
{
    // the head element is  the first child of the HTMLHtmlElement that is a HTMLHeadElement; if there are no head
    // elements, then return nullptr - this is handled by returning a deference of the begin pointer
    auto html_element_child_nodes = *get_m_html_element()->child_nodes();
    auto head_elements = html_element_child_nodes | ranges::views::cast_all_to<html::elements::html_head_element>();
    return *head_elements.begin();
}


auto dom::nodes::document::get_title()
        const -> ext::string
{
    // the title element is either the first SVGTitleElement of the document element, if the document element is an
    // SvgElement. otherwise it is the first HTMLTitleElement of this document
    auto* title_element = dynamic_cast<svg::elements::svg_element*>(document_element())
            ? ranges::front(*document_element->child_nodes() | ranges::views::cast_all_to<svg::elements::svg_title_element>())
            : get_m_title_element();

    // the value of the xxxTitleElement is the child text content of it, with the ascii whitespace stripped and
    // collapsed from the string
    auto value = detail::tree_internals::child_text_content(title_element);
    value = infra::detail::infra_string_internals::strip_and_collapse_ascii_whitespace(value);
    return value;
}


auto dom::nodes::document::get_body()
        const -> html::elements::html_body_element*
{
    // the body element is the first child of the HTMLHtmlElement that is a HTMLBodyElement; if there are no body
    // elements, then return nullptr - this is handled by returning a deference of the begin pointer
    auto html_element_child_nodes = *get_m_html_element()->child_nodes();
    auto body_children = html_element_child_nodes | ranges::views::cast_all_to<html::elements::html_body_element>();
    return *body_children.begin();
}


auto dom::nodes::document::get_images()
        const -> ranges::any_view<html::elements::html_image_element*>
{
    // the HTMLImageElements in this Document are all the HTMLImageElements that are descendants of this Document (live
    // collection)
    return detail::tree_internals::descendants(this)
            | ranges::views::cast_all_to<html::elements::html_image_element>();
}


auto dom::nodes::document::get_links()
        const -> ranges::any_view<html::elements::html_link_element*>
{
    // the HTMLLinkElements in this Document are all the HTMLLinkElements that are descendants of this Document (live
    // collection), and have their href attribute set
    return detail::tree_internals::descendants(this)
            | ranges::views::cast_all_to<html::elements::html_link_element>()
            | ranges::views::filter([](html::elements::html_link_element* element) {return element->href();});
}


auto dom::nodes::document::get_forms()
        const -> ranges::any_view<html::elements::html_form_element*>
{
    // the HTMLFormElements in this Document are all the HTMLFormElements that are descendants of this Document (live
    // collection)
    return detail::tree_internals::descendants(this)
            | ranges::views::cast_all_to<html::elements::html_form_element>();
}


auto dom::nodes::document::get_scripts()
        const -> ranges::any_view<html::elements::html_script_element*>
{
    // the HTMLScriptElements in this Document are all the HTMLScriptElements that are descendants of this Document
    // (live collection)
    return detail::tree_internals::descendants(this)
            | ranges::views::cast_all_to<html::elements::html_script_element>();
}


auto dom::nodes::document::get_dir()
        const -> ext::string
{
    // if the 'document_element' exists, and is a HTMLElement based object, then forward its 'dir' attribute value as
    // the Document's 'dir' attribute value, otherwise the empty string
    auto* html_document_element = dynamic_cast<html::elements::html_element*>(document_element());
    return html_document_element ? html_document_element->dir() : "";
}


auto dom::nodes::document::set_cookie(
        ext::string_view val)
        -> void
{
    // if this Document is cookie averse, then it is not in the correct condition to return the value of the cookie, so
    // return the empty string instead.
    return_if (html::detail::document_internals::is_cookie_averse_document(this));

    // if the origin of this Document is opaque, then throw a security error, because the security of the cookie cannot
    // be guaranteed, despite the Document not being cookie averse
    detail::exception_internals::throw_v8_exception_formatted<SECURITY_ERR>(
            [this] {return m_origin.is_opaque();},
            "Can not get the cookie of a Document whose origin is opaque");

    // set the true value of the cookie t the new cookie value passed in as a parameter
    *cookie = val;
}


auto dom::nodes::document::set_ready_state(
        ext::string_view val)
        -> void
{
    *ready_state = val;
    if (/* TODO : HTML parser association */ false)
    {
        JS_REALM_GET_RELEVANT(this)
        auto now = high_resolution_time::detail::time_internals::current_high_resolution_time(this_relevant_global_object);
        if (val == "complete" && m_load_timing_info.dom_complete_time == 0)
            m_load_timing_info.dom_complete_time = now;

        if (val == "interactive" && m_load_timing_info.dom_interactive_time == 0)
            m_load_timing_info.dom_interactive_time = now;
    }
    detail::event_internals::fire_event("readystatechange", this);
}


auto dom::nodes::document::set_title(
        ext::string_view val)
        -> void
{
    using namespace detail::namespace_internals;

    // if the document element is an SvgTitleElement, handle the title updating steps for the SVG namespace
    if (dynamic_cast<svg::elements::svg_element*>(document_element()))
    {
        // set the 'title_element' to the first child of the 'document_element's child node that is an SvgTitleElement;
        // if there is no such element, then create the element, and insert it as the first child of the
        // 'document_element' (call insert not pre_insert, because the newly created 'title_element' can't be the first
        // child when it has just been created)
        auto* title_element = ranges::front(*document_element->child_nodes() | ranges::views::cast_all_to<svg::elements::svg_title_element>());
        if (!title_element)
        {
            title_element = detail::customization_internals::create_an_element(document_element->owner_document(), "title", SVG);
            detail::mutation_internals::insert(title_element, document_element(), document_element->first_child());
        }

        // replace all the text in the SvgTitleElement with the new title value 'val' parameter
        detail::node_internals::string_replace_all(val, title_element);
    }

    else if (document_element->namespace_uri() == HTML)
    {
        auto* title_element = get_m_title_element();
        return_if(!title_element && !head());
        if (!title_element)
        {
            title_element = dynamic_cast<html::elements::html_title_element*>(detail::customization_internals::create_an_element(document_element->owner_document(), "title", HTML));
            detail::mutation_internals::append(title_element, head());
        }

        // replace all the text in the HtmlTitleElement with the new title value 'val' parameter
        detail::node_internals::string_replace_all(val, title_element);
    }
}


auto dom::nodes::document::set_body(
        html::elements::html_body_element* val)
        -> void
{
    // don't do anything id the new body value is the same as the current body, ie the first HTMLBodyElement of the
    // HTMLHtmlElement in this Document
    return_if (body() == val);

    // if there is a current HTMLBodyElement (and an implied 'document_element'), then replace it with the new
    // HTMLBodyElement
    if (body())
        detail::mutation_internals::replace(body(), body->parent_node(), val);

    // if there is no implied HTMLBodyElement, and no 'document_element', throw a hierarchy request error, because it's
    // not possible to append the HTMLBodyElement to a non-existent 'document_element'
    detail::exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            [this] {return !document_element();},
            "Document must have a document element, if a new HTMLBodyElement is being added to the Document");

    // append the HTMLBodyElement to this Document's 'document_element'
    detail::mutation_internals::append(val, document_element());
}


auto dom::nodes::document::get_m_html_element()
        const -> html::elements::html_html_element*
{
    // the HTMLHtmlElement of a Document is the 'document_element', if it is a HTMLHtmlElement, otherwise a nullptr; the
    // dynamic cast will either return the cast document element, or nullptr if the document element isn't a
    // HTMLHtmlElement
    return dynamic_cast<html::elements::html_html_element*>(document_element());
}


auto dom::nodes::document::get_m_title_element()
        const -> html::elements::html_title_element*
{
    // the HTMLTitleElement of a Document is the first HTMLTitleElement in the Document's descendants; if there isn't
    // one, then nullptr is returned, as the de-referenced begin() iterator
    return ranges::front(detail::tree_internals::descendants(this) | ranges::views::cast_all_to<html::elements::html_title_element*>());
}


auto dom::nodes::document::operator[](
        const ext::string& name)
        -> ranges::any_view<element*>
{
    // return all descendant element in this tree whose name attribute (only present on certain element interfaces) is
    // equal to the 'name' parameter; TODO: named_element mixin with property `name` -> cast all, filter, and cast back
    return detail::tree_internals::descendants(this)
            | ranges::views::filter([name](element* descendant) {return descendant->name() == name;});
}

auto dom::nodes::document::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<document>{isolate}
            .auto_wrap_objects();
}
