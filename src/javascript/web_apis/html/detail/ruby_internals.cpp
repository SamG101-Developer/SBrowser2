#include "ruby_internals.hpp"

#include "ext/assertion.hpp"

#include "html/elements/html_element.hpp"


auto html::detail::segmentation_categorization_ruby_element(
        const elements::html_element* root)
        -> ext::vector<ext::string>
{
    ASSERT(root->local_name() == "ruby");
    ext::vector<ext::string> base_text_segments;
    ext::vector<ext::string> annotation_segments;

    // TODO : finish WITHOUT goto statements
}
