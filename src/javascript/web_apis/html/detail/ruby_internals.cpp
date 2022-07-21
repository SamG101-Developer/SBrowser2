#include "ruby_internals.hpp"

#include "ext/assert.hpp"

#include "html/elements/html_element.hpp"


auto html::detail::ruby::segmentation_categorization_ruby_element(
        elements::html_element* root)
        -> ext::vector<ext::string>
{
    ext::assert_true(root->local_name() == "ruby");
    ext::vector<ext::string> base_text_segments;
    ext::vector<ext::string> annotation_segments;

    // TODO : finish WITHOUT goto statements
}
