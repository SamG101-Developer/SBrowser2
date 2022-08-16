#ifndef SBROWSER2_ATTRIBUTE_INTERNALS_HPP
#define SBROWSER2_ATTRIBUTE_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/optional.hpp"
#include "ext/string.hpp"
namespace dom::nodes {class attr;}
namespace dom::nodes {class element;}
namespace dom::nodes {class document;}


namespace dom::detail
{
    // handle changes
    auto handle_attributes_changes(
            const nodes::attr* attribute,
            nodes::element* owner_element,
            ext::string_view old_value,
            ext::string_view new_value)
            -> void;

    // general mutations to attributes
    auto change(
            nodes::attr* attribute,
            ext::string_view new_value)
            -> nodes::attr*;

    auto append(
            nodes::attr* attribute,
            nodes::element* new_owner_element)
            -> nodes::attr*;

    auto remove(
            nodes::attr* attribute)
            -> nodes::attr*;

    auto replace(
            nodes::attr* old_attribute,
            nodes::attr* new_attribute)
            -> nodes::attr*;

    auto create(
            ext::string_view local_name,
            ext::string_view namespace_ = "",
            ext::string_view value = "",
            ext::string_view prefix = "",
            nodes::document* owner_document = nullptr)
            -> nodes::attr;

    auto set_attribute(
            nodes::element* new_owner_element,
            nodes::attr* attribute)
            -> nodes::attr*;

    auto remove_attribute(
            const nodes::element* owner_element,
            nodes::attr* attribute)
            -> nodes::attr*;

    auto toggle_attribute(
            nodes::element* owner_element,
            nodes::attr* attribute,
            ext::optional<ext::boolean> force,
            ext::string_view qualified_name = "",
            ext::string_view namespace_ = "")
            -> nodes::attr*;

    // setter helpers
    auto set_existing_attribute_value(
            nodes::attr* attribute,
            ext::string_view value)
            -> void;
}


#endif //SBROWSER2_ATTRIBUTE_INTERNALS_HPP
