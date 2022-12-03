#include "html_element_internals.hpp"

#include "ext/casting.ixx"



#include "environment/reflection.hpp"

#include "dom/mixins/slottable.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/detail/event_internals.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/detail/namespace_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/detail/text_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_fragment.hpp"
#include "dom/nodes/text.hpp"
#include "dom/other/dom_implementation.hpp"

#include "html/detail/context_internals.hpp"
#include "html/detail/document_internals.hpp"
#include "html/detail/lazy_loading_internals.hpp"
#include "html/detail/miscellaneous_internals.hpp"
#include "html/detail/policy_internals.hpp"
#include "html/detail/render_blocking_internals.hpp"
#include "html/detail/task_internals.hpp"
#include "html/elements/html_base_element.hpp"
#include "html/elements/html_body_element.hpp"
#include "html/elements/html_dlist_element.hpp"
#include "html/elements/html_iframe_element.hpp"
#include "html/elements/html_meta_element.hpp"
#include "html/elements/html_olist_element.hpp"
#include "html/elements/html_time_element.hpp"
#include "html/elements/html_title_element.hpp"
#include "html/mixins/html_hyperlink_element_utils.hpp"

#include "fetch/detail/body_internals.hpp"
#include "fetch/detail/http_internals.hpp"
#include "fetch/detail/request_internals.hpp"
#include "fetch/detail/response_internals.hpp"

#include "content_security_policy/detail/csp_internals.hpp"
#include "infra/detail/infra_strings_internals.hpp"
#include "intersection_observer/detail/algorithm_internals.hpp"

#include <magic_enum.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/range/operations.hpp>
#include <range/v3/view/drop_while.hpp>


auto html::detail::advisory_information(
        dom::nodes::element* element)
        -> ext::string
{
    // if the element is a HTMLTitleElement, then return the text value of the element; this is the behaviour that other
    // elements try to achieve as-well, by propagating the ancestors until one of them is a HMTLTitleElement
    if (decltype(auto) title_element = dynamic_cast<elements::html_title_element*>(element))
        return title_element->text();

    // if the parent element of an element is an Element or subclass, then all the advisory method with the parent
    // element (this might not get the actual text value, but assuming a parent in the ancestor chain is a
    // HTMLTitleElement, the text will eventually propagate back down the function call chain)
    if (decltype(auto) parent_element = element->parent_element())
        return advisory_information(parent_element);

    // if the element isn't a HTMLTitleElement, and there is no parent element of 'html_element', then return the
    // default value, which is an empty string
    return u8"";
}


auto html::detail::determine_language(
        dom::nodes::element* element)
        -> ext::string
{
    // TODO : this is an incorrect implementation
    // the closest ancestor to the 'html_element' whose 'xml:lang' attribute is set, or 'lang' attribute is set, and
    // the element is a HTMLxxx element, is the language that is used,
    auto ancestors = dom::detail::ancestors(element);
    auto valid_ancestors = ancestors
            | ranges::views::cast_all_to<elements::html_element*>()
            | ranges::views::filter([](elements::html_element* element)
            {
                return element->lang() && element->namespace_uri() == dom::detail::XML
                || element->lang() && dynamic_cast<elements::html_element*>(element);
            });

    return valid_ancestors.front() ? valid_ancestors.front()->lang() : "";
}


auto html::detail::translate_enabled(
        dom::nodes::element* element)
        -> ext::boolean
{
    // an element is translatable if its 'translate' attribute is set to "yes"; this can only be applied to HTMLxxx
    // elements, so false is returned for non-html elements as well as html elements whose translate attribute is set to
    // "no"
    if (auto* html_element = dynamic_cast<elements::html_element*>(element))
        return html_element->translate() == "yes";
    return false;
}


auto html::detail::directionality(
        dom::nodes::element* element)
        -> directionality_t
{
    using enum bidirectional_char_t;
    using enum directionality_t;

    // create a boolean to check is the attribute exists (set in javascript block, so define the variable outside the
    // block
    ext::boolean has_ltr_attribute;

    // check if the 'dir' attribute is present on the element
    JS_BLOCK_ENTER
        JS_REALM_GET_RELEVANT(element)
        has_ltr_attribute = reflect_has_attribute_value(element, "ltr", element_relevant);
    JS_BLOCK_EXIT

    // cast the Element to a HTMLElement and a HTMLTextAreaElement (both can be nullptr) - they are used in further
    // checks below to determine directionality in unique conditions
    auto* html_element = dynamic_cast<elements::html_element*>(element);
    auto* html_text_area_element = dynamic_cast<elements::html_text_area_element*>(html_element);

    // if the attribute isn't set, but the HTMLElement is a document element, then return LTR (document element
    // directionality defaults to LTR if unspecified)
    if (!has_ltr_attribute && dom::detail::is_document_element(element))
        return LTR;

    // if the HTMLElement's 'dir' attribute is set to "ltr" then use the attribute, and return LTR
    if (html_element && html_element->dir() == "ltr")
        return LTR;

    // if the HTMLElement's 'dir' attribute is set to "rtl" then use the attribute, and return RTL
    if (html_element && html_element->dir() == "rtl")
        return RTL;

    // if the element is a HTMLTextAreaElement and the 'dir' attribute is set to "auto", then check the contents of the
    // element to determine the directionality of the HTMLTextAreaElement (this is the algorithm that "auto" follows for
    // HTMLTextArea elements)
    if (html_text_area_element && html_text_area_element->dir() == "auto")
    {
        // if the HTMLTextArea contents contains an AL or R character with no L character preceding it, then return an
        // RTL directionality (AL / R are RTL characters)
        if (ranges::contains(html_text_area_element->text(), AL) || ranges::contains(html_text_area_element->text(), R)) // TODO : and no L before it
            return RTL;

        // if there is no text, but the HTMLTextAreaElement is a document element, then return LTR (document element
        // directionality defaults to LTR if unspecified)
        if (!html_text_area_element->text().empty() || dom::detail::is_document_element(html_text_area_element))
            return LTR;

        // otherwise, return the directionality of the parent element - this is because if there is one RTL condition in
        // the parent's directionality check that returns true, then RTL overrides the possible LTR nature of this
        // HTMLTextAreaElement
        return directionality(html_text_area_element->parent_element());
    }

    // if the element isn't a HTMLTextAreaElement and the 'dir' attribute is set to "auto", then check the descendant
    // text content to determine the directionality of the non-HTMLTextAreaElement (this is the algorithm that "auto"
    // follows for non-HTMLTextAreaElements)
    if (html_element->dir() == "auto" || html_element->local_name() == "bdi" && !has_ltr_attribute)
    {
        // set the black list of element types that won;t be checked for text contents (irrelevant to the textual
        // display on the screen)
        auto black_list_element_types = {"bdi", "script", "style", "textarea"};

        // get all the descendant text nodes of the non-HTMLTextAreaElement who don't have blacklisted-type element
        // ancestors, and join their data together into one string
        auto text_nodes_data = dom::detail::descendant_text_nodes(html_element)
                | ranges::views::remove_if([&black_list_element_types](dom::nodes::text* text_node)
                {
                    auto ancestor_local_names = dom::detail::ancestors(text_node)
                            | ranges::views::cast_all_to<dom::nodes::element>()
                            | ranges::views::transform([](dom::nodes::element* element) {return element->local_name();});
                    return ranges::any_of(ancestor_local_names, ext::bind_back(ranges::contains, std::move(black_list_element_types)));
                })
                | ranges::views::transform([](dom::nodes::text* text_node) {return text_node->data();})
                | ranges::to<ext::string>();

        // get the first AL / R / L character in the 'text_nodes_data' string
        char32_t character = ranges::first_where(
                text_nodes_data,
                [](char32_t character) {return ranges::contains(ext::initializer_list<char32_t>{AL, L, R}, character);});

        // if the first directionality-defining character is L, thn return LTR, otherwise return RTL (the character has
        // to be AL / R otherwise)
        if (character)
            return character == L ? LTR : RTL;

        // if there is no directionality-defining character, but the HTMLTextAreaElement is a document element, then
        // return LTR (document element directionality defaults to LTR if unspecified)
        if (dom::detail::is_document_element(html_element))
            return LTR;

        // if the element isn't a document element, then return the directionality of the parent element
        return directionality(html_element->parent_element());
    }

    // if all other conditions aren't met, then return the directionality of the parent element
    if (element->parent_element() && !has_ltr_attribute)
        return directionality(element->parent_element());
}


auto html::detail::directionality_of_attribute(
        dom::nodes::element* element,
        ext::string_view attribute)
        -> directionality_t
{
    using enum bidirectional_char_t;
    using enum directionality_t;

    // create the list of directionality-capable attributes, ie attributes that can have text with a specific
    // directionality (maps attribute name to valid element local names)
    ext::map<ext::string_view, ext::vector<ext::string>> directionality_capable_attributes
    {
        {"abbr", {"th"}},
        {"alt", {"area", "img"}},
        {"content", {"meta"}},
        {"label", {"optgroup", "option", "track"}},
        {"placeholder", {"textarea"}},
        {"title", {"*"}}
    };

    auto html_element = dynamic_cast<elements::html_element*>(element);

    // if the attribute name is in the map of attribute to local names, the html element's 'dir' is in the "auto" state,
    // and one of the valid local names matches the local name of 'element', then enter this block
    if (auto matching_elements = directionality_capable_attributes.at(attribute);
            matching_elements.has_value()
            && html_element && html_element->dir() == "auto"
            && ranges::any_of(matching_elements.value(), [element](auto valid_local_name) {return valid_local_name == "*" || valid_local_name == element->local_name();}))
    {
        // get the value of the attribute is the relevant javascript realm, using a javascript reflection macro
        ext::string attribute_value;
        JS_BLOCK_ENTER
            JS_REALM_GET_RELEVANT(element)
            attribute_value = reflect_get_attribute_value(element, attribute, ext::string, element_relevant);
        JS_BLOCK_EXIT

        // get the first AL / R / L character in the 'text_nodes_data' string
        char32_t character = ranges::first_where(
                attribute_value,
                [](char32_t character) {return ranges::contains(ext::initializer_list<char32_t>{AL, L, R}, character);});

        // if the first directionality-defining character is L, thn return LTR, otherwise return RTL (the character has
        // to be AL / R otherwise)
        if (character == R || character == AL)
            return RTL;

        return LTR;
    }

    // otherwise, return the directionality of the element who the desired attribute belongs to, as a default / backup
    // option
    return directionality(element);
}


auto html::detail::rendered_text_collection_steps(
        dom::nodes::node* node)
        -> ranges::any_view<ext::string>
{
    auto items = *node->child_nodes()
                 | ranges::views::transform(rendered_text_collection_steps)
                 | ranges::views::join;

    // TODO : computed value [CSS-CASCADE] -> return items

    return_if(!being_rendered(node)) items;

    // TODO : css spec stuff

    return items;
}



auto html::detail::rendered_text_fragment(
        ext::string_view input,
        dom::nodes::document* document)
        -> std::unique_ptr<dom::nodes::document_fragment>&&
{
    // create an ext::string copy of the 'input' string_view, and set the 'text' string to an empty string; the
    // 'fragment' is a new DocumentFragment, and the 'position' currently points to the first item in the 'input_copy'
    // string
    ext::string input_copy = input;
    ext::string text;
    decltype(auto) fragment = std::make_unique<dom::nodes::document_fragment>();
    decltype(auto) position = input_copy.begin();

    // loop until the 'position' iterator points to past the last element in the 'input_copy' string
    while (position != input_copy.end())
    {
        // collect code points from the 'input_copy' string until a LF or CR character is reached; this is where each
        // new textual piece of data is defined, so stop at the newline
        text = infra::detail::collect_code_points_not_matching(input_copy, position, char(0x00a), char(0x000d));

        // if there is text (ie not empty newlines), then create a new Text node that contains the 'text' as its data,
        // and append it to the fragment node; this adds the new Text node to the DocumentFragment
        if (!text.empty())
        {
            decltype(auto) text_node = std::make_unique<dom::nodes::text>(std::move(text))
            text_node_d_func()->owner_document = document;
            dom::detail::append(std::move(text_node), fragment);
        }

        // if there are more newlines following the newline that the data is split on, then add a new <br> element to
        // the DocumentFragment, to kep the newlines in formatting
        while (position != input_copy.end())
        {
            if (*position == char(0x00d) && *std::next(position) == 0x000a) ++position;
            ++position;

            auto&& element = dom::detail::create_an_element(document, "br", dom::detail::HTML);
            dom::detail::append(element, fragment);
        }
    }

    // return the newly populated fragment, that can be used to replace all in another node (ie like being used to set
    // the '[inner/outer]_text' of a HTMLxxxElement
    return std::move(fragment);
}


auto html::detail::merge_with_next_text_node(
        dom::nodes::text* text_node)
        -> void
{
    // The 'next_text_node' is the next sibling of 'text_node', if it's a Text node, otherwise it is nullptr (ie a
    // non-Text node, meaning that this algorithm can't complete), so return if the 'next_text_node' is nullptr
    auto* next_text_node = dynamic_cast<dom::nodes::text*>(text_node->next_sibling());
    return_if(!next_text_node);

    // append the 'next_text_node's data to the 'text_node', and if 'next_text_node' has a parent node, then remove it
    // from its parent
    text_node->append_data(next_text_node->data());
    if (next_text_node->parent_node())
        dom::detail::remove(next_text_node);
}


auto html::detail::get_elements_target(
        const dom::nodes::element* element)
        -> ext::string
{
    JS_REALM_GET_RELEVANT(element);
    if (reflect_has_attribute_value(element, "target", element_relevant))
        return reflect_get_attribute_value(element, "target", ext::string, element_relevant);

    auto base_elements = dom::detail::root(element)->child_nodes
            | ranges::views::cast_all_to<html::elements::html_base_element*>()
            | ranges::views::filter([](html::elements::html_base_element* html_base_element) {JS_REALM_GET_RELEVANT(html_base_element) return reflect_has_attribute_value(html_base_element, "target", html_base_element_relevant);});

    return !base_elements.empty() ? base_elements.front() : "";
}


auto html::detail::contact_information(
        dom::nodes::element* element)
        -> ext::vector<dom::nodes::element*>
{
    auto local_names = {"article", "body"};

    // if the 'element' is an article or body element, then get all the descendant's of the 'element' that are article
    // elements, excluding any elements that have an article or body ancestor element, that is a descendant of the
    // 'element'
    if (ranges::contains(local_names, element->local_name()))
        return dom::detail::descendants(element)
                | ranges::views::cast_all_to<dom::nodes::element*>()
                | ranges::views::filter([](dom::nodes::element* descendant) {return descendant->local_name() == "article";})
                | ranges::views::filter([local_names, element](dom::nodes::element* descendant)
                {
                    auto ancestors = dom::detail::ancestors(descendant);
                    auto clamped = ranges::subrange(ranges::find(ancestors, element), ancestors.end());
                    auto filtered = clamped | ranges::views::filter([local_names](dom::nodes::element* ancestor) {return ranges::contains(local_names, ancestor->local_name());});
                    return !filtered.empty();
                });

    // if the 'element' has ancestors that are article or body nodes, then return the contact information of the closest
    // ancestor article or body node
    if (auto element_ancestors = dom::detail::ancestors(element) | ranges::views::cast_all_to<dom::nodes::element*>();
            ranges::any_of(element_ancestors, [local_names](dom::nodes::element* ancestor) {return ranges::contains(local_names, ancestor->local_name());}))

        return contact_information(ranges::back(element_ancestors
                | ranges::views::remove(element)
                | ranges::views::filter([local_names](dom::nodes::element* ancestor) {return ranges::contains(local_names, ancestor->local_name());})));

    // if the 'element's document has a HTMLBodyElement, then return the contact information for this HTMLBodyElement
    if (auto* html_body_element = element->owner_document()->body())
        return contact_information(html_body_element);

    // otherwise, there is no contact information for this node
    return {};
}


auto html::detail::ordinal_value(
        elements::html_element* owner_element)
        -> ext::number<int>
{
    auto* html_olist_owner_element = dynamic_cast<elements::html_olist_element*>(owner_element);
    ext::number<int> i = 1;
    ext::number<int> numbering = html_olist_owner_element ? starting_value(html_olist_owner_element) : 1;

    // TODO
}


auto html::detail::set_frozen_base_url(
        elements::html_base_element* element)
        -> void
{
    auto* document = element->owner_document();
    auto document_fallback_base_url = fallback_base_url(document);
    auto url_record = url::detail::parse(element->href(), document_fallback_base_url, document->m_encoding);

    element->m_frozen_base_url = content_security_policy::detail::is_base_allowed_for_document(url_record, document)
            ? document_fallback_base_url
            : url_record;
}


auto html::detail::pragma_set_default_language(
        elements::html_meta_element* element)
        -> void
{
    JS_REALM_GET_RELEVANT(element)
    return_if (!reflect_has_attribute_value(element, "content", element_relevant));
    return_if (ranges::contains(element->content(), ','));

    auto input = element->content();
    auto position = ranges::find(input, ' ');
    auto candidate = infra::detail::collect_code_points_not_matching(input, position, ' ');

    return_if(candidate.empty());

    // TODO : set some value to 'candidate' <- return for now?
}


auto html::detail::starting_value(
        elements::html_olist_element* element)
        -> ext::number<long>
{
    JS_REALM_GET_RELEVANT(element)
    if (reflect_has_attribute_value(element, "start", element_relevant))
        return element->start();

    return element->reversed() ? ranges::size(element->children() | ranges::views::cast_all_to<elements::html_olist_element*>()) : 1;
}


auto html::detail::name_value_groups(
        elements::html_dlist_element* element)
        -> name_value_groups_t
{
    // create the 'groups' which is a list of pairs, a 'current' pair, and a 'seen_dd' boolean, defaulted to false
    name_value_groups_t groups;
    name_value_group_t current;
    auto seen_dd = ext::boolean::FALSE_();

    // create the 'child' and 'grand_child' pointers; initialize the 'child' to the first child of the 'element', and
    // the 'grand_child' is set to nullptr (cast as a Node)
    auto* child = element->first_child();
    auto* grand_child = static_cast<dom::nodes::node*>(nullptr);

    // continue iterating until all the child nodes of 'element' have been visited (next sibling of the last child is
    // nullptr (not an error), so the loop will finish smoothly)
    while (child)
    {
        // the HTMLDivElement means to check for grand-children
        if (auto* cast_child = dynamic_cast<dom::nodes::element*>(child); cast_child->local_name() == "div")
        {
            // initialize the 'grand_child' to the first child of the 'child', continue iterating until all the child
            // nodes of 'child' have been visited (all the grandchildren whose parent is 'child')
            grand_child = child->first_child();
            while (grand_child)
            {
                // process the element and move onto the next grandchild (if it's not nullptr)
                process_dt_dd_element(grand_child, groups, current, seen_dd);
                grand_child = grand_child->next_sibling();
            }
        }

        // process the element and move onto the next child (if it's not nullptr)
        else
        {
            process_dt_dd_element(child, groups, current, seen_dd);
            child = child->next_sibling();
        }
    }
}


auto html::detail::process_dt_dd_element(
        dom::nodes::node* node,
        name_value_groups_t& groups,
        name_value_group_t& current,
        ext::boolean& seen_dd)
        -> void
{
    // cast the child to a HTMLElement (required for dom::nodes::element::local_name, as well as being the type required
    // for the group(s)
    auto* cast_child = dynamic_cast<elements::html_element*>(node);

    // handle the case where the 'cast_child' is a "dt" element
    if (cast_child->local_name() == "dt")
    {
        // if a "dd" element has already been seen (and there is therefore elements in the value section of 'current',
        // then push 'current' into 'groups', set 'seen_dd' to false, and push 'cast_child' into the name section of a
        // new group
        if (seen_dd)
        {
            groups.push_back(current);
            current = name_value_group_t{};
            seen_dd = false;
        }

        current.first.push_back(cast_child);
    }

    // handle the case where the 'cast_child' is a "dd" element
    else if (cast_child->local_name() == "dd")
    {
        // push 'cast_child' to the value section of the 'groups', and set 'seen_dd' to true - this means that when the
        // next "dt" element is found, this "dd" element will be the last in the 'current' group, and the 'current'
        // group will be pushed to 'groups'
        current.second.push_back(cast_child);
        seen_dd = true;
    }
}


auto html::detail::date_time_value(
        elements::html_time_element* element)
        -> ext::string
{

    // if the element still has the 'date_time' attribute, then return it, otherwise return the child text content of
    // the element, which represents the date time instead
    JS_REALM_GET_RELEVANT(element)
    return reflect_has_attribute_value(element, "dateTime", element_relevant)
            ? element->date_time()
            : dom::detail::child_text_content(element);
}


auto html::detail::set_url(
        mixins::html_hyperlink_element_utils* element)
        -> void
{
    // if the element doesn't still have the 'href' attribute, then return an empty url object, otherwise parse the url
    // internal attribute of the element relative to the element's document, and set the element url to the new url
    // record that has been generated
    JS_REALM_GET_RELEVANT(element)
    element->m_url = !reflect_has_attribute_value(element, "href", element_relevant)
            ? url::detail::url_t{}
            : parse_url(element->m_url, ext::cross_cast<dom::nodes::element*>(element)->owner_document()).second;
}


auto html::detail::reinitialize_url(
        mixins::html_hyperlink_element_utils* element)
        -> void
{
    // don't do anything if the url h=exists and has a "blob" scheme, otherwise for any other normal url is "http(s)"
    // urls etc, call the 'set_url(...)' function
    return_if (element->m_url && element->m_url->scheme() == "blob") // TODO : && ..._has_opaque_path(element->m_url)
    set_url(element);
}


auto html::detail::update_href(
        mixins::html_hyperlink_element_utils* element)
        -> void
{
    // set the element's href attribute to the serialization of the elements url internal attribute
    element->href = serialize_url(element->m_url);
}


auto html::detail::process_iframe_attributes(
        elements::html_iframe_element* element,
        ext::boolean initial_insertion)
        -> void
{
    auto navigate_to_srcdoc_resource = [&element]
    {
        fetch::detail::response_t response
        {
            .url_list = {"abort:srcdoc"},
            .header_list = {{"Content-Type", "text/html"}},
            .body = fetch::detail::body_t {.source = element->srcdoc()};
        };
        navigate_iframe_or_frame(element, response);
    };

    if (!element->srcdoc().empty())
    {
        element->m_current_navigation_lazy_loaded = false;
        if (will_lazy_load_element_steps(element))
        {
            element->m_lazy_load_resumption_steps = std::move(navigate_to_srcdoc_resource);
            element->m_current_navigation_lazy_loaded = true;
            start_intersection_observing_lazy_loading_element(element);
            return;
        }

        navigate_to_srcdoc_resource();
    }
    else
        shared_attribute_processing_steps_for_iframe_and_frame_elements(element, initial_insertion);
}


auto html::detail::shared_attribute_processing_steps_for_iframe_and_frame_elements(
        elements::html_iframe_element* element,
        ext::boolean initial_insertion)
        -> void
{
    auto navigate_to_resource = [&element](fetch::detail::request_t& resource)
    {
        navigate_iframe_or_frame(element, resource);
    };

    url::detail::url_t url_record {"about:blank"};

    JS_REALM_GET_RELEVANT(element)
    if (reflect_has_attribute_value(element, "src", element_relevant) && !element->src().empty())
        url_record = parse_url(element->src(), element->owner_document()).second;

    return_if (ranges::any_of(
            ancestor_browsing_contexts(element->m_nested_browsing_context),
            [&url_record](context_internals::browsing_context* context) {return context->active_document()->url() == url_record;}));

    if (matches_about_blank(url_record) && initial_insertion)
    {
        // TODO : update history
        iframe_load_event_steps(element);
        return;
    }

    fetch::detail::request_t resource
    {
        .url = url_record,
        .referrer_policy = magic_enum::enum_cast<referrer_policy::referrer_policy_t>(element->referrer_policy())
    };

    if (element->local_name() == "iframe")
        element->m_current_navigation_lazy_loaded = false;

    if (element->local_name() == "iframe" && will_lazy_load_element_steps(element))
    {
        element->m_lazy_load_resumption_steps = ext::bind_front(std::move(navigate_to_resource), resource);
        element->m_current_navigation_lazy_loaded = true;
        start_intersection_observing_lazy_loading_element(element);
        return;
    }

    navigate_to_resource(resource);
}


template <type_is<fetch::detail::response_t, fetch::detail::request_t> T>
auto html::detail::navigate_iframe_or_frame(
        const elements::html_iframe_element* element,
        T&& resource)
        -> void
{
    ext::string history_handling = completely_loaded(element->m_nested_browsing_context->active_document())
            ? "replace"
            : "default";

    auto* document = element->owner_document(); JS_REALM_GET_RELEVANT(document)
    dom::detail::queue_element_task(networking_task_source, element,
            [&resource, &document_relevant_global_object]
            {fetch::detail::report_timing(resource, document_relevant_global_object);});

    // TODO : finish
}


auto html::detail::iframe_load_event_steps(
        const elements::html_iframe_element* element)
        -> void
{
    ASSERT(element->m_nested_browsing_context);
    auto child_document = element->m_nested_browsing_context->active_document();
    return_if(child_document->m_mute_iframe_flag);
    child_document->m_mute_iframe_flag = true;
    dom::detail::fire_event("load", element);
    child_document->m_mute_iframe_flag = false;
}
