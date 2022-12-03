#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_FORM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_FORM_INTERNALS_HPP


#include "ext/string.hpp"
#include "ext/variant.ixx"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(html)
namespace dom::nodes {class node;}
namespace encoding {class encoding;}
namespace html::elements {class html_element;}
namespace html::elements {class html_form_element;}


namespace html::detail
{
    auto supported_property_names()
            -> ext::vector<ext::string>;

    auto determine_value_of_named_property(
            ext::string_view name)
            -> dom::nodes::node*;

    auto default_button(
            html::elements::html_form_element* element)
            -> html::elements::html_element*;

    auto create_entry(
            ext::string_view name,
            ext::variant<ext::string, file_api::file*>,
            ext::string_view filename = "")
            -> detail::entry_t;

    auto construct_entry_list(
            html::elements::html_form_element* element)
            -> detail::entry_list_t;

    auto pick_encoding_form_form(
            html::elements::html_form_element* element)
            -> encoding::encoding;

    auto convert_list_of_name_value_pairs(
            ext::vector<ext::pair<ext::string, ext::string>>&& list)
            -> entry_list_t;

    auto multipart_form_data_encoding_algorithm(
            const entry_list_t& entry_list,
            encoding::encoding* encoding)
            -> void;

    auto text_plain_encoding_algorithm(
            ext::vector<ext::pair<ext::string, ext::string>>&& entry_list,
            encoding::encoding* encoding)
            -> void;

    auto reset_form(
            html::elements::html_form_element* element)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_FORM_INTERNALS_HPP
