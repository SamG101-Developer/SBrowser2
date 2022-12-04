#ifndef SBROWSER2_TEXT_INTERNALS_HPP
#define SBROWSER2_TEXT_INTERNALS_HPP



#include "ext/type_traits.ixx"
namespace dom::nodes {class character_data;}
namespace dom::nodes {class text;}


namespace dom::detail
{
    auto replace_data(
            nodes::character_data* text_node,
            ext::number<ulong> offset,
            ext::number<ulong> count,
            ext::string&& data)
            -> void;

    auto substring_data(
            const nodes::character_data* text_node,
            ext::number<ulong> offset,
            ext::number<ulong> count)
            -> ext::string;

    auto split(
            nodes::character_data* existing_text_node,
            ext::number<ulong> offset)
            -> std::unique_ptr<nodes::text>;
}


#endif //SBROWSER2_TEXT_INTERNALS_HPP
