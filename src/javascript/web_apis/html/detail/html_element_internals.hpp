#pragma once
#ifndef SBROWSER2_HTML_ELEMENT_INTERNALS_HPP
#define SBROWSER2_HTML_ELEMENT_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/number.hpp"
#include "ext/pair.hpp"
#include "ext/span.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include <range/v3/view/any_view.hpp>
namespace dom::nodes {class node;}
namespace dom::nodes {class document;}
namespace dom::nodes {class document_fragment;}
namespace dom::nodes {class element;}
namespace dom::nodes {class text;}
namespace fetch::detail::request_internals {class internal_request;}
namespace fetch::detail::response_internals {class internal_response;}
namespace html::elements {class html_base_element;}
namespace html::elements {class html_div_element;} // TODO : make this a #include in .cpp file
namespace html::elements {class html_dlist_element;}
namespace html::elements {class html_element;}
namespace html::elements {class html_iframe_element;}
namespace html::elements {class html_meta_element;}
namespace html::elements {class html_olist_element;}
namespace html::elements {class html_style_element;}
namespace html::elements {class html_time_element;}
namespace html::mixins {class html_hyperlink_element_utils;}


namespace html::detail::html_element_internals
{
    enum class directionality_t {LTR, RTL, AUTO};
    enum class bidirectional_char_t: char32_t {L = 0x200e, R = 0x200f, AL = 0x061c, EN, ES, ET, AN, CS, NSM, BN, B, S, WS, ON, LRE, LRO, RLE, PDF, LRI, RLI, FSI, PDI};

    using name_value_group_t = ext::pair<ext::vector<elements::html_element*>, ext::vector<elements::html_element*>>;
    using name_value_groups_t = ext::vector<name_value_group_t>;

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

    auto contact_information(
            dom::nodes::element* element)
            -> ext::span<dom::nodes::element*>;

    auto list_owner(
            dom::nodes::element* element)
            -> elements::html_element*;

    auto ordinal_value(
            elements::html_element* owner_element)
            -> ext::number<int>;

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

    // HTMLOListElement
    auto starting_value(
            elements::html_olist_element* element)
            -> ext::number<long>;

    // HTMLDListElement
    auto name_value_groups(
            elements::html_dlist_element* element)
            -> name_value_groups_t ;

    auto process_dt_dd_element(
            dom::nodes::node* node,
            name_value_groups_t & groups,
            name_value_group_t & current,
            ext::boolean& seen_dd)
            -> void;

    // HTMLTimeElement
    auto date_time_value(
            elements::html_time_element* element)
            -> ext::string;

    auto machine_readable_equivalent_element_content(
            elements::html_time_element* element)
            -> ext::string;

    // HTMLHyperlinkElementUtils
    auto set_url(
            mixins::html_hyperlink_element_utils* element)
            -> void;

    auto reinitialize_url(
            mixins::html_hyperlink_element_utils* element)
            -> void;

    auto update_href(
            mixins::html_hyperlink_element_utils* element)
            -> void;

    // HTMLIFrameElement
    auto process_iframe_attributes(
            elements::html_iframe_element* element,
            ext::boolean_view initial_insertion = false)
            -> void;

    auto shared_attribute_processing_steps_for_iframe_and_frame_elements(
            elements::html_iframe_element* element,
            ext::boolean_view initial_insertion = false)
            -> void;

    template <type_is<fetch::detail::response_internals::internal_response, fetch::detail::request_internals::internal_request> T>
    auto navigate_iframe_or_frame(
            const elements::html_iframe_element* element,
            T&& resource)
            -> void;

    auto iframe_load_event_steps(
            const elements::html_iframe_element* element)
            -> void;
}


#endif //SBROWSER2_HTML_ELEMENT_INTERNALS_HPP
