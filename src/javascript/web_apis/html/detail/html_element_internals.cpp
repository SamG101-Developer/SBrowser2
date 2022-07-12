#include "html_element_internals.hpp"

#include "ext/functional.hpp"
#include "ext/ranges.hpp"

#include "environment/reflection.hpp"

#include "dom/mixins/slottable.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/detail/namespace_internals.hpp"
#include "dom/detail/text_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_fragment.hpp"
#include "dom/nodes/text.hpp"
#include "dom/other/dom_implementation.hpp"

#include "html/elements/html_title_element.hpp"
#include "html/detail/render_blocking_internals.hpp"

#include "infra/detail/infra_strings_internals.hpp"

#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/view/drop_while.hpp>


auto html::detail::html_element_internals::advisory_information(
        dom::nodes::element* element)
        -> ext::string
{
    // if the element is a HTMLTitleElement, then return the text value of the element; this is the behaviour that other
    // elements try to achieve as-well, by propagating the ancestors until one of them is a HMTLTitleElement
    if (auto* title_element  = dynamic_cast<elements::html_title_element*>(element))
        return title_element->text();

    // if the parent element of an element is an Element or subclass, then all the advisory method with the parent
    // element (this might not get the actual text value, but assuming a parent in the ancestor chain is a
    // HTMLTitleElement, the text will eventually propagate back down the function call chain)
    if (auto* parent_element = element->parent_element())
        return advisory_information(parent_element);

    // if the element isn't a HTMLTitleElement, and there is no parent element of 'html_element', then return the
    // default value, which is an empty string
    return "";
}


auto html::detail::html_element_internals::determine_language(
        dom::nodes::element* element)
        -> ext::string
{
    using namespace dom::detail::namespace_internals;

    // TODO : this is an incorrect implementation
    // the closest ancestor to the 'html_element' whose 'xml:lang' attribute is set, or 'lang' attribute is set, and
    // the element is a HTMLxxx element, is the language that is used,
    auto ancestors = dom::detail::tree_internals::ancestors(element);
    auto valid_ancestors = ancestors
            | ranges::views::cast_all_to<elements::html_element*>()
            | ranges::views::filter([](elements::html_element* element) {return element->lang() && element->namespace_uri() == XML || element->lang() && dynamic_cast<elements::html_element*>(element);});

    return valid_ancestors.front() ? valid_ancestors.front()->lang() : "";
}


auto html::detail::html_element_internals::translate_enabled(
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


auto html::detail::html_element_internals::directionality(
        dom::nodes::element* element)
        -> directionality_t
{
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
    if (!has_ltr_attribute && dom::detail::tree_internals::is_document_element(element))
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
        if (!html_text_area_element->text().empty() || dom::detail::tree_internals::is_document_element(html_text_area_element))
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
        std::initializer_list<ext::string> black_list_element_types {"bdi", "script", "style", "textarea"};

        // get all the descendant text nodes of the non-HTMLTextAreaElement who don't have blacklisted-type element
        // ancestors, and join their data together into one string
        auto text_nodes_data = dom::detail::tree_internals::descendant_text_nodes(html_element)
                | ranges::views::remove_if([&black_list_element_types](dom::nodes::text* text_node)
                {
                    auto ancestor_local_names = dom::detail::tree_internals::ancestors(text_node)
                            | ranges::views::cast_all_to<dom::nodes::element>()
                            | ranges::views::transform([](dom::nodes::element* element) {return element->local_name();});
                    return ranges::any_of(ancestor_local_names, ext::bind_back(ranges::contains, std::move(black_list_element_types)));
                })
                | ranges::views::transform([](dom::nodes::text* text_node) {return text_node->data();})
                | ranges::to<ext::string>();

        // get the first AL / R / L character in the 'text_nodes_data' string
        char32_t character = ranges::first_where(
                text_nodes_data,
                [](char32_t character) {return ranges::contains(std::initializer_list<char32_t>{AL, L, R}, character);});

        // if the first directionality-defining character is L, thn return LTR, otherwise return RTL (the character has
        // to be AL / R otherwise)
        if (character)
            return character == L ? LTR : RTL;

        // if there is no directionality-defining character, but the HTMLTextAreaElement is a document element, then
        // return LTR (document element directionality defaults to LTR if unspecified)
        if (dom::detail::tree_internals::is_document_element(html_element))
            return LTR;

        // if the element isn't a document element, then return the directionality of the parent element
        return directionality(html_element->parent_element());
    }

    // if all other conditions aren't met, then return the directionality of the parent element
    if (element->parent_element() && !has_ltr_attribute)
        return directionality(element->parent_element());
}


auto html::detail::html_element_internals::directionality_of_attribute(
        dom::nodes::element* element,
        ext::string_view attribute)
        -> directionality_t
{
    // create the list of directionality-capable attributes, ie attributes that can have text with a specific
    // directionality (maps attribute name to valid element local names)
    ext::map<ext::string, ext::string_vector> directionality_capable_attributes
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
                [](char32_t character) {return ranges::contains(std::initializer_list<char32_t>{AL, L, R}, character);});

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


auto html::detail::html_element_internals::rendered_text_collection_steps(
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



auto html::detail::html_element_internals::rendered_text_fragment(
        ext::string_view input,
        dom::nodes::document* document)
        -> dom::nodes::document_fragment*
{
    using namespace dom::detail::namespace_internals;

    // create an ext::string copy of the 'input' string_view, and set the 'text' string to an empty string; the
    // 'fragment' is a new DocumentFragment, and the 'position' currently points to the first item in the 'input_copy'
    // string
    ext::string input_copy = input;
    ext::string text;
    auto* fragment = std::make_unique<dom::nodes::document_fragment>().get();
    auto  position = input_copy.begin();

    // loop until the 'position' iterator points to past the last element in the 'input_copy' string
    while (position != input_copy.end())
    {
        // collect code points from the 'input_copy' string until a LF or CR character is reached; this is where each
        // new textual piece of data is defined, so stop at the newline
        text = infra::detail::infra_string_internals::collect_code_points_not_matching(input_copy, position, char(0x00a), char(0x000d));

        // if there is text (ie not empty newlines), then create a new Text node that contains the 'text' as its data,
        // and append it to the fragment node; this adds the new Text node to the DocumentFragment
        if (!text.empty())
        {
            dom::nodes::text text_node {text};
            text_node.owner_document = document;
            dom::detail::mutation_internals::append(&text_node, fragment);
        }

        // if there are more newlines following the newline that the data is split on, then add a new <br> element to
        // the DocumentFragment, to kep the newlines in formatting
        while (position != input_copy.end())
        {
            if (*position == char(0x00d) && *std::next(position) == 0x000a) ++position;
            ++position;

            auto* element = dom::detail::customization_internals::create_an_element(document, "br", HTML);
            dom::detail::mutation_internals::append(element, fragment);
        }
    }

    // return the newly populated fragment, that can be used to replace all in another node (ie like being used to set
    // the '[inner/outer]_text' of a HTMLxxxElement
    return fragment;
}


auto html::detail::html_element_internals::merge_with_next_text_node(
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
        dom::detail::mutation_internals::remove(next_text_node);
}
