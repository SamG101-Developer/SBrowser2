export module apis.dom_parser.detail;

import ext.string;
import ext.vector;

namespace dom {class document_fragment;}
namespace dom {class element;}
namespace dom {class node;}


namespace dom_parsing::detail
{
    auto fragment_parsing_algorithm(
            ext::string&& markup_string,
            dom::element* context_element)
            -> dom::document_fragment;

    auto fragment_serializing_algorithm(
            dom::node* node)
            -> ext::string;

    auto html_serialization(
            dom::node* node)
            -> ext::string;

    auto xml_serialization(
            dom::node* node)
            -> ext::string;

    auto xml_serialization_algorithm(
            dom::node* node,
            ext::string_view namespace_uri,
            namespace_prefix_map_t&& prefix_map,
            generated_namespace_prefix_index_t&& prefix_index,
            ext::boolean require_well_formed)
            -> ext::string;

    auto produce_document_type_serialization(
            dom::node* node,
            ext::boolean require_wel_formed_flag)
            -> ext::string;

    auto record_namespace_information(
            dom::element* element,
            namespace_prefix_map_t&& prefix_map,
            ext::vector<ext::string>&& element_prefixes_list,
            ext::string_view duplicate_prefix_definition)
            -> ext::string;

    auto generate_prefix(
            namespace_prefix_map_t&& prefix_map,
            ext::string&& new_namespace_uri,
            generated_namespace_prefix_index_t&& prefix_index)
            -> ext::string;

    auto xml_serialization_of_attributes(
            dom::element* elemebt,
            namespace_prefix_map_t&& prefix_map,
            generated_namespace_prefix_index_t&& prefix_index,
            ext::boolean ignore_namespace_definition_attribute,
            ext::string_view duplicate_prefix_definition,
            ext::boolean require_wel_formed)
            -> ext::string;

    auto serialize_attribute_value(
            ext::string_view attribute_value,
            ext::boolean required_well_formed)
            -> ext::string;
}
