#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_RUBY_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_RUBY_INTERNALS_HPP


#include "ext/string.hpp"
#include "ext/vector.hpp"
namespace dom::nodes {class node;}
namespace html::elements {class html_element;}

namespace html::detail
{
    auto segmentation_categorization_ruby_element(
            const elements::html_element* root)
            -> ext::vector<ext::string>;

    auto set_the_current_base_text(
            ext::vector<ext::string> base_text_segments,
            const dom::nodes::node* current_parent,
            ext::number<int> start_index,
            ext::number<int> end_index)
            -> void;

    auto push_ruby_level(
            const dom::nodes::node* current_parent,
            ext::number<int> index)
            -> void;

    auto pop_ruby_level(
            const dom::nodes::node* current_parent,
            ext::number<int> index)
            -> void;

    auto push_ruby_annotation(
            const dom::nodes::node* current_parent,
            ext::number<int> index)
            -> void;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_RUBY_INTERNALS_HPP
