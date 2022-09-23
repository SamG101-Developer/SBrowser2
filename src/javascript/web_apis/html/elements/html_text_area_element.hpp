#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TEXT_AREA_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TEXT_AREA_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/validatable.hpp"
namespace html::elements {class html_text_area_element;}

#include INCLUDE_INNER_TYPES(html)
namespace html::elements {class html_form_element;}


class html::elements::html_text_area_element
        : public html_element
        , public mixins::validatable
{
public constructors:
    DOM_CTORS(html_text_area_element);
    html_text_area_element() = default;

public js_methods:
    auto select() -> void;
    auto set_range_text(ext::string&& replacement, ext::number<long> start = 0, ext::number<long> end = 0, detail::selection_mode_t selection_mode = detail::selection_mode_t::PRESERVE) -> void;
    auto set_selection_range(ext::number<long> start, ext::number<long> end, detail::selection_mode_t selection_mode);

private js_properties:
    ext::property<ext::string> autocomplete;
    ext::property<ext::number<ulong>> cols;
    ext::property<ext::number<ulong>> rows;
    ext::property<ext::number<long>> max_length;
    ext::property<ext::number<long>> min_length;
    ext::property<html::elements::html_form_element*> form;
    ext::property<ext::boolean> disabled;
    ext::property<ext::boolean> read_only;
    ext::property<ext::boolean> required;
    ext::property<ext::string> dir_name;
    ext::property<ext::string> name;
    ext::property<ext::string> placeholder;
    ext::property<detail::wrap_type_t> wrap;
    ext::property<ext::string> type;
    ext::property<ext::string> default_value;
    ext::property<ext::string> value;
    ext::property<ext::number<ulong>> text_length;
    ext::property<std::unique_ptr<ext::vector<dom::nodes::node*>>> labels;

    ext::property<ext::number<ulong>> selection_start;
    ext::property<ext::number<ulong>> selection_end;
    ext::property<ext::string> selection_direction;

private cpp_properties:
    ext::boolean m_dirty_value_flag;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TEXT_AREA_ELEMENT_HPP
