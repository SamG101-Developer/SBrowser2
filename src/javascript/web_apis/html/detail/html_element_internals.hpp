#pragma once
#ifndef SBROWSER2_HTML_ELEMENT_INTERNALS_HPP
#define SBROWSER2_HTML_ELEMENT_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include <range/v3/view/any_view.hpp>
namespace dom::nodes {class node;}
namespace dom::nodes {class document;}
namespace dom::nodes {class document_fragment;}
namespace dom::nodes {class element;}
namespace dom::nodes {class text;}
namespace html::elements {class html_base_element;}
namespace html::elements {class html_element;}
namespace html::elements {class html_meta_element;}
namespace html::elements {class html_style_element;}


namespace html::detail::html_element_internals
{
    enum class directionality_t {LTR, RTL, AUTO};
    enum class bidirectional_char_t {L = 0x200e, R = 0x200f, AL = 0x061c, EN, ES, ET, AN, CS, NSM, BN, B, S, WS, ON, LRE, LRO, RLE, PDF, LRI, RLI, FSI, PDI};

    // title attribute
    auto advisory_information(
            dom::nodes::element* element)
            -> ext::string;

    // lang attribute
    auto determine_language(
            dom::nodes::element* element)
            -> ext::string;

    // translate attribute
    auto translate_enabled(
            dom::nodes::element* element)
            -> ext::boolean;

    // dir attribute
    auto directionality(
            dom::nodes::element* element)
            -> directionality_t;

    auto directionality_of_attribute(
            dom::nodes::element* element,
            ext::string_view attribute)
            -> directionality_t;

    // inner / outer text attribute
    auto rendered_text_collection_steps(
            dom::nodes::node* node)
            -> ranges::any_view<ext::string>;

    auto rendered_text_fragment(
            ext::string_view input,
            dom::nodes::document* document)
            -> dom::nodes::document_fragment*;

    auto merge_with_next_text_node(
            dom::nodes::text* text_node)
            -> void;

    // target attribute (HTMLBaseElement)
    auto get_elements_target(
            const dom::nodes::element* element) // TODO -> change type to 'HTML_[Link/Area/Form]_Element'
            -> ext::string;

    // HTMLElement miscellaneous functions
    auto contributes_script_blocking_style_sheet(
            dom::nodes::element* element,
            dom::nodes::document* document)
            -> ext::boolean;

    // HTMLBaseElement
    auto set_frozen_base_url(
            elements::html_base_element* element)
            -> void;

    // HTMLMetaElement
    auto pragma_set_default_language(
            elements::html_meta_element* element)
            -> void;

    // HTMLStyleElement
    auto update_style_block(
            elements::html_style_element* element)
            -> void;
}


#endif //SBROWSER2_HTML_ELEMENT_INTERNALS_HPP
