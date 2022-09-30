#include "document.hpp"
#include "dom/_typedefs.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/detail/tree_internals.hpp"

#include "ext/casting.hpp"
#include "ext/ranges.hpp"
#include "html/detail/origin_internals.hpp"
#include "javascript/environment/realms_2.hpp"

#include "dom/detail/event_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/detail/namespace_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/range_internals.hpp"
#include "dom/events/event.hpp"
#include "dom/nodes/attr.hpp"
#include "dom/nodes/cdata_section.hpp"
#include "dom/nodes/comment.hpp"
#include "dom/nodes/document_fragment.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/processing_instruction.hpp"
#include "dom/nodes/shadow_root.hpp"
#include "dom/nodes/window.hpp"
#include "dom/other/dom_implementation.hpp"
#include "dom/ranges/range.hpp"

#include "html/detail/document_internals.hpp"
#include "html/elements/html_body_element.hpp"
#include "html/elements/html_head_element.hpp"
#include "html/elements/html_html_element.hpp"
#include "html/elements/html_link_element.hpp"
#include "html/elements/html_script_element.hpp"
#include "html/elements/html_title_element.hpp"
#include "html/other/location.hpp"

#include "file_api/detail/blob_internals.hpp"
#include "hr_time/detail/time_internals.hpp"
#include "infra/detail/infra_strings_internals.hpp"
#include "permissions_policy/permissions_policy.hpp"
#include "svg/elements/svg_title_element.hpp"
#include "url/detail/url_internals.hpp"

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
{
    INIT_PIMPL(document);
    ACCESS_PIMPL(document);

    JS_REALM_GET_SURROUNDING(this);
    d->url = std::make_unique<url::detail::url_t>("about:blank");
    d->content_type = "application/xml";
    d->ready_state = "complete";
    d->origin = v8pp::from_v8<window*>(this_surrounding_agent, this_surrounding_global_object)->origin;
    d->get_the_parent =
            [this, d](events::event* event)
            {
                JS_REALM_GET_RELEVANT(this);
                return_if(event->d_func()->type == "load" || !d->browsing_context) ext::nullptr_cast<event_target*>();

                decltype(auto) global_object = v8pp::from_v8<event_target*>(this_relevant_agent, this_relevant_global_object);
                return global_object;
            };

    permissions_policy()->m_associated_node = this;
}


auto dom::nodes::document::create_element(
        ext::string&& local_name,
        ext::map<ext::string, ext::any>&& options)
        const -> element
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const document);

        // create the html adjusted local name and namespace, and get the 'is' option from the options dictionary - set it
        // to the empty string otherwise
        auto html_adjusted_local_name = detail::html_adjust_string(std::move(local_name), d->type == "html");
        auto html_adjusted_namespace_ = d->type == "html" || d->content_type == "application/xhtml+xml" ? detail::HTML : "";
        auto is = options.try_emplace("is", "").first->second.to<ext::string>();

        // create the Element node with the html adjusted variables
        return detail::create_an_element(this, html_adjusted_local_name, html_adjusted_namespace_, "", is, true);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::document::create_element_ns(
        ext::string&& namespace_,
        ext::string&& qualified_name,
        ext::map<ext::string, ext::any>&& options)
        const -> element
{
    CE_REACTIONS_METHOD_DEF
        // determine the 'prefix' and 'local_name' from the 'namespace_' and 'qualified_name', using the detail
        // 'validate_and_extract(...)' method
        auto [prefix, local_name] = detail::validate_and_extract(std::move(namespace_), std::move(qualified_name));
        auto is = options.try_emplace("is", "").first->second.to<ext::string>();

        // create the Element node with the html adjusted variables
        return detail::create_an_element(this, local_name, std::move(namespace_), prefix, is, true);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::document::create_document_fragment()
        const -> document_fragment
{
    // create a DocumentFragment node, and set its owner document to this document
    auto node = document_fragment{};
    node.d_func()->node_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_text_node(
        ext::string&& data)
        const -> text
{
    // create a Text node, and set its data and owner document to the 'data' parameter and this document
    auto node = text{};
    node.d_func()->data = std::move(data);
    node.d_func()->node_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_cdata_section_node(
        ext::string&& data)
        const -> cdata_section
{
    ACCESS_PIMPL(const document);
    using enum detail::dom_exception_error_t;

    detail::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
            [this, type = d->type] {return type == "html";},
            "Cannot create a CDataSection node in a HTML Document");

    detail::throw_v8_exception_formatted<INVALID_CHARACTER_ERR>(
            [data = std::move(data)] {return data.contains("]]>");},
            "Cannot create a CDataSection node with ']]>' in the data");

    auto node = cdata_section{};
    node.d_func()->data = std::move(data);
    node.d_func()->node_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_comment(
        ext::string&& data)
        const -> comment
{
    auto node = comment{};
    node.d_func()->data = std::move(data);
    node.d_func()->node_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_processing_instruction(
        ext::string&& target,
        ext::string&& data)
        const -> processing_instruction
{
    using enum detail::dom_exception_error_t;

    detail::throw_v8_exception_formatted<INVALID_CHARACTER_ERR>(
            [data = std::move(data)] {return data.contains("?>");},
            "Cannot create a CDataSection node with '?>' in the data");

    auto node = processing_instruction{};
    node.d_func()->data = std::move(data);
    node.d_func()->target = std::move(target);
    node.d_func()->node_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_attribute(
        ext::string&& local_name)
        const -> attr
{
    ACCESS_PIMPL(const document);
    auto html_adjusted_local_name = d->type == "html"
            ? local_name | ranges::views::lowercase() | ranges::to<ext::string>
            : std::move(local_name);

    auto node = attr{};
    node.d_func()->local_name = html_adjusted_local_name;
    node.d_func()->node_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_attribute_ns(
        ext::string&& namespace_,
        ext::string&& qualified_name)
        const -> attr
{
    auto [prefix, local_name] = detail::validate_and_extract(std::move(namespace_), std::move(qualified_name));

    attr node;
    node.d_func()->local_name = std::move(local_name);
    node.d_func()->namespace_prefix = std::move(prefix);
    node.d_func()->namespace_ = std::move(namespace_);
    node.d_func()->node_document = const_cast<document*>(this);
    return node;
}


auto dom::nodes::document::create_range()
        const -> node_ranges::range
{
    auto live_range = node_ranges::range{};

    ext::tie(live_range->d_func()->start->node, live_range.d_func()->start->offset) = ext::make_tuple(const_cast<document*>(this), 0);
    ext::tie(live_range->d_func()->end->node, live_range->d_func()->end->offset) = ext::make_tuple(const_cast<document*>(this), 0);
    return live_range;
}


auto dom::nodes::document::import_node(
        node* new_node,
        ext::boolean deep)
        -> node*
{
    using enum detail::dom_exception_error_t;

    CE_REACTIONS_METHOD_DEF
        detail::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
                [new_node] {return ext::multi_cast<nodes::document*, nodes::shadow_root*>(new_node);},
                "Node being imported cannot be a Document or ShadowRoot");

        // to import a node, a clone of the node is made, with the Document set tot this node; the node is basically copied
        // into this Document
        return detail::clone(new_node, this, true);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::document::adopt_node(
        node* new_node)
        -> node*
{
    using enum detail::dom_exception_error_t;

    CE_REACTIONS_METHOD_DEF
        detail::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(
                [new_node] {return ext::multi_cast<nodes::document*>(new_node);},
                "Node being imported cannot be a Document");

        detail::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                [new_node] {return ext::multi_cast<nodes::shadow_root*>(new_node);},
                "Node being imported cannot be a ShadowRoot");

        // to adopt a node, the node is moved, not copied, from its current Document node to this Document Node; no cloning
        // takes place
        return detail::adopt(new_node, this);
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::document::get_last_modified()
        const -> decltype(this->last_modified)::value_t
{
    // get the string epoch time (eg "1563566272"), and convert it to a 'long long' number type. convert this into a c++
    // time object with a strict format, push this into a stream, and finally return the string that the
    // std::stringstream holds.
    std::time_t decimal_time = std::stoll(*last_modified);
    auto formatted_time = std::stringstream{} << std::put_time(std::localtime(&decimal_time), "%m/%d/%Y %H:%M:%S");
    return formatted_time.str();
}


auto dom::nodes::document::get_cookie()
        const -> decltype(this->cookie)::value_t
{
    // if this Document is cookie averse, then it is not in the correct condition to return the value of the cookie, so
    // return the empty string instead.
    return_if (html::detail::is_cookie_averse_document(this)) "";

    // if the origin of this Document is opaque, then throw a security error, because the security of the cookie cannot
    // be guaranteed, despite the Document not being cookie averse
    detail::throw_v8_exception_formatted<SECURITY_ERR>(
            [this] {return html::detail::is_opaque_origin(m_origin);},
            "Can not get the cookie of a Document whose origin is opaque");

    // return the true value of the cookie
    guard_property(cookie);
    return *cookie;
}


auto dom::nodes::document::get_head()
        const -> decltype(this->head)::value_t
{
    // the head element is  the first child of the HTMLHtmlElement that is a HTMLHeadElement; if there are no head
    // elements, then return nullptr - this is handled by returning a deference of the begin pointer
    decltype(auto) html_element_child_nodes = *get_m_html_element()->child_nodes();
    decltype(auto) head_elements = html_element_child_nodes | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<html::elements::html_head_element*>();
    return *head_elements.begin();
}


auto dom::nodes::document::get_title()
        const -> decltype(this->title)::value_t
{
    // the title element is either the first SVGTitleElement of the document element, if the document element is an
    // SvgElement. otherwise it is the first HTMLTitleElement of this document
    decltype(auto) title_element = dynamic_cast<svg::elements::svg_element*>(document_element())
            ? ranges::front(*document_element()->child_nodes() | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<svg::elements::svg_title_element*>())
            : get_m_title_element();

    // the value of the xxxTitleElement is the child text content of it, with the ascii whitespace stripped and
    // collapsed from the string
    auto value = detail::child_text_content(title_element);
    value = infra::detail::strip_and_collapse_ascii_whitespace(value);
    return value;
}


auto dom::nodes::document::get_body()
        const -> decltype(this->body)::value_t
{
    // the body element is the first child of the HTMLHtmlElement that is a HTMLBodyElement; if there are no body
    // elements, then return nullptr - this is handled by returning a deference of the begin pointer
    decltype(auto) html_element_child_nodes = *get_m_html_element()->child_nodes();
    decltype(auto) body_children = html_element_child_nodes | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<html::elements::html_body_element*>();
    return body_children.front();
}


auto dom::nodes::document::get_images()
        const -> decltype(this->images)::value_t
{
    // the HTMLImageElements in this Document are all the HTMLImageElements that are descendants of this Document (live
    // collection)
    return detail::descendants(this)
            | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<html::elements::html_image_element*>();
}


auto dom::nodes::document::get_links()
        const -> decltype(this->links)::value_t
{
    // the HTMLLinkElements in this Document are all the HTMLLinkElements that are descendants of this Document (live
    // collection), and have their href attribute set
    return detail::descendants(this)
            | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<html::elements::html_link_element*>()
            | ranges::views::filter([](html::elements::html_link_element* element) {return element->href();});
}


auto dom::nodes::document::get_forms()
        const -> decltype(this->forms)::value_t
{
    // the HTMLFormElements in this Document are all the HTMLFormElements that are descendants of this Document (live
    // collection)
    return detail::descendants(this)
            | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<html::elements::html_form_element*>();
}


auto dom::nodes::document::get_scripts()
        const -> decltype(this->scripts)::value_t
{
    // the HTMLScriptElements in this Document are all the HTMLScriptElements that are descendants of this Document
    // (live collection)
    return detail::descendants(this)
            | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<html::elements::html_script_element*>();
}


auto dom::nodes::document::get_dir()
        const -> decltype(this->dir)::value_t
{
    // if the 'document_element' exists, and is a HTMLElement based object, then forward its 'dir' attribute value as
    // the Document's 'dir' attribute value, otherwise the empty string
    auto* html_document_element = dynamic_cast<html::elements::html_element*>(document_element());
    return html_document_element ? html_document_element->dir() : "";
}


auto dom::nodes::document::set_cookie(
        const ext::string& val)
        -> void
{
    // if this Document is cookie averse, then it is not in the correct condition to return the value of the cookie, so
    // return the empty string instead.
    return_if (html::detail::is_cookie_averse_document(this));

    // if the origin of this Document is opaque, then throw a security error, because the security of the cookie cannot
    // be guaranteed, despite the Document not being cookie averse
    detail::throw_v8_exception_formatted<SECURITY_ERR>(
            [this] {return html::detail::is_opaque_origin(m_origin);},
            "Can not get the cookie of a Document whose origin is opaque");

    // set the true value of the cookie t the new cookie value passed in as a parameter
    *cookie = val;
}


auto dom::nodes::document::set_ready_state(
        const ext::string& val)
        -> void
{
    guard_property(ready_state);
    *ready_state = val;

    if (/* TODO : HTML parser association */ false)
    {
        JS_REALM_GET_RELEVANT(this);
        auto now = hr_time::detail::current_hr_time(this_relevant_global_object);
        if (val == "complete" && m_load_timing_info->dom_complete_time == 0)
            m_load_timing_info->dom_complete_time = now;

        if (val == "interactive" && m_load_timing_info->dom_interactive_time == 0)
            m_load_timing_info->dom_interactive_time = now;
    }
    
    detail::fire_event("readystatechange", this);
}


auto dom::nodes::document::set_title(
        const ext::string& val)
        -> void
{
    using namespace detail;

    // if the document element is an SvgTitleElement, handle the title updating steps for the SVG namespace
    if (dynamic_cast<svg::elements::svg_element*>(document_element()))
    {
        // set the 'title_element' to the first child of the 'document_element's child node that is an SvgTitleElement;
        // if there is no such element, then create the element, and insert it as the first child of the
        // 'document_element' (call insert not pre_insert, because the newly created 'title_element' can't be the first
        // child when it has just been created)
        decltype(auto) title_element = ranges::front(document_element()->children() | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<svg::elements::svg_title_element*>());
        if (!title_element)
        {
            title_element = detail::create_an_element(document_element()->owner_document(), "title", SVG);
            detail::insert(title_element, document_element(), document_element()->first_child());
        }

        // replace all the text in the SvgTitleElement with the new title value 'val' parameter
        detail::string_replace_all(val, title_element);
    }

    else if (document_element()->namespace_uri() == HTML)
    {
        return_if(!get_m_title_element() && !head());
        decltype(auto) title_element = dynamic_cast<dom::nodes::element*>(get_m_title_element());

        if (!title_element)
        {
            title_element = detail::create_an_element(document_element()->owner_document(), "title", HTML);
            detail::append(title_element, head());
        }

        // replace all the text in the HtmlTitleElement with the new title value 'val' parameter
        detail::string_replace_all(val, title_element);
    }
}


auto dom::nodes::document::set_body(
        html::elements::html_body_element* const& val)
        -> void
{
    // don't do anything id the new body value is the same as the current body, ie the first HTMLBodyElement of the
    // HTMLHtmlElement in this Document
    return_if (body() == val);

    // if there is a current HTMLBodyElement (and an implied 'document_element'), then replace it with the new
    // HTMLBodyElement
    if (val)
        detail::replace(body(), body()->parent_node(), val);

    // if there is no implied HTMLBodyElement, and no 'document_element', throw a hierarchy request error, because it's
    // not possible to append the HTMLBodyElement to a non-existent 'document_element'
    detail::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
            [this] {return !document_element();},
            "Document must have a document element, if a new HTMLBodyElement is being added to the Document");

    // append the HTMLBodyElement to this Document's 'document_element'
    detail::append(val, document_element());
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
    return ranges::front(detail::descendants(this) | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<html::elements::html_title_element*>());
}


auto dom::nodes::document::operator[](
        const ext::string& name)
        -> ranges::any_view<element*>&
{
    // return all descendant element in this tree whose name attribute (only present on certain element interfaces) is
    // equal to the 'name' parameter; TODO: named_element concept with property `name` -> cast all, filter, and cast back
    return detail::descendants(this)
            | ranges::views::filter([name](element* descendant) {return descendant->name() == name;});
}


auto dom::nodes::document::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<document>{isolate}
        .auto_wrap_objects();

    return std::move(conversion);
}
