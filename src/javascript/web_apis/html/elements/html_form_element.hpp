#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FORM_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FORM_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/validatable.hpp"
#include "ext/vector_like.hpp"
namespace html::elements {class html_form_element;}


class html::elements::html_form_element
        : public html_element
        , public mixins::validatable
        , public ext::vector_like_linked<html_element*>
{
public constructors:
    DOM_CTORS(html_form_element);
    html_form_element() = default;

public js_methods:
    auto submit() -> void;
    auto request_submit(html_element* submitter = nullptr);
    auto reset() -> void;

private js_properties:
    ext::property<ext::string> accept_charset;
    ext::property<ext::string> action;
    ext::property<ext::string> autocomplete;
    ext::property<ext::string> enctype;
    ext::property<ext::string> encoding;
    ext::property<ext::string> method;
    ext::property<ext::string> name;
    ext::property<ext::boolean> no_validate;
    ext::property<ext::string> target;
    ext::property<ext::string> rel;
    ext::property<std::unique_ptr<ext::vector<html_element*>>> elements;

public cpp_operators:
    auto operator[](ext::string_view index) -> html_element*& override;

private cpp_properties:
    ext::map<ext::string, html_element*> m_past_map;
    ext::boolean m_constructing_entry_list;
    ext::boolean m_firing_submission_events;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FORM_ELEMENT_HPP
