#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_VALIDATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_VALIDATION_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/tuple.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(html)
namespace html::elements {class html_element;};
namespace html::elements {class html_form_element;};


namespace html::detail
{
    auto statically_validate_constraints(
            html::elements::html_form_element* form)
            -> ext::tuple<ext::boolean, ext::vector<html::elements::html_element*>>;

    auto interactively_validate_constraints(
            html::elements::html_form_element* form)
            -> ext::tuple<ext::boolean, ext::vector<html::elements::html_element*>>;

    auto check_validity_steps(
            html::elements::html_element* element)
            -> ext::boolean;
};


struct html::detail::validity_state_t
{
    ext::boolean value_missing;
    ext::boolean type_mismatch;
    ext::boolean pattern_mismatch;
    ext::boolean too_long;
    ext::boolean too_short;
    ext::boolean range_underflow;
    ext::boolean range_overflow;
    ext::boolean step_mismatch;
    ext::boolean bad_input;
    ext::boolean custom_error;
    ext::boolean valid;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_VALIDATION_INTERNALS_HPP
