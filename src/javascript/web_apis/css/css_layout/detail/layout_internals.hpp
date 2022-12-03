#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_LAYOUT_DETAIL_LAYOUT_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_LAYOUT_DETAIL_LAYOUT_INTERNALS_HPP


#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(css/css_layout)


namespace css::detail
{
};


struct css::detail::layout_definition_t
{
    v8::Local<v8::Function> class_constructor;
    v8::Local<v8::Function> layout_function;
    v8::Local<v8::Function> intrinsic_sizes_function;

    ext::boolean constructor_valid_flag;
    ext::vector<ext::string> input_properties;
    ext::vector<ext::string> child_input_properties;
    layout_options_t layout_options;
};


struct css::detail::document_layout_definition_t
{
    ext::vector<ext::string> input_properties;
    ext::vector<ext::string> child_input_properties;
    layout_options_t layout_options;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_LAYOUT_DETAIL_LAYOUT_INTERNALS_HPP
