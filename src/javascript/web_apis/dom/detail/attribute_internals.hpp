#ifndef SBROWSER2_ATTRIBUTE_INTERNALS_HPP
#define SBROWSER2_ATTRIBUTE_INTERNALS_HPP


#include "ext/optional.ixx"

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
            ext::string&& new_value)
            -> nodes::attr*;

    auto append(
            std::unique_ptr<nodes::attr>&& attribute,
            nodes::element* new_owner_element)
            -> nodes::attr*;

    auto remove(
            nodes::attr* attribute)
            -> std::unique_ptr<nodes::attr>;

    auto replace(
            nodes::attr* old_attribute,
            std::unique_ptr<nodes::attr>&& new_attribute)
            -> nodes::attr*;

    auto create(
            ext::string&& local_name,
            ext::string&& namespace_ = u"",
            ext::string&& value = u"",
            ext::string&& prefix = u"",
            nodes::document* owner_document = nullptr)
            -> std::unique_ptr<nodes::attr>;

    auto set_attribute(
            nodes::element* new_owner_element,
            std::unique_ptr<nodes::attr> attribute)
            -> nodes::attr*;

    auto remove_attribute(
            const nodes::element* owner_element,
            nodes::attr* attribute)
            -> nodes::attr*;

    auto toggle_attribute(
            nodes::element* owner_element,
            nodes::attr* attribute,
            ext::optional<ext::boolean> force,
            ext::string_view qualified_name = u"",
            ext::string_view namespace_ = u"")
            -> nodes::attr*;

    // setter helpers
    auto set_existing_attribute_value(
            nodes::attr* attribute,
            ext::string&& value)
            -> void;

    // other

}


#endif //SBROWSER2_ATTRIBUTE_INTERNALS_HPP
