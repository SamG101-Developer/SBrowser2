#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FORM_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FORM_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/validatable.hpp"
#include "ext/vector_like.hpp"
namespace html::elements {class html_form_element;}
namespace html::elements {class html_form_element_private;}


class html::elements::html_form_element
        : public html_element
        , public mixins::validatable
        , public ext::vector_like_linked<html_element*>
{
public constructors:
    DOM_CTORS(html_form_element);
    MAKE_PIMPL(html_form_element);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto submit() -> void;
    auto request_submit(html_element* submitter = nullptr);
    auto reset() -> void;

private js_properties:
    DEFINE_GETTER(accept_charset, ext::string_view);
    DEFINE_GETTER(action, ext::string_view);
    DEFINE_GETTER(autocomplete, ext::string_view);
    DEFINE_GETTER(enctype, ext::string_view);
    DEFINE_GETTER(encoding, ext::string);
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(no_validate, ext::boolean);
    DEFINE_GETTER(target, ext::string_view);
    DEFINE_GETTER(rel, ext::string_view);
    DEFINE_GETTER(elements, ranges::any_helpful_view<html::elements::html_element*>);

    DEFINE_SETTER(accept_charset, ext::string);
    DEFINE_SETTER(action, ext::string);
    DEFINE_SETTER(autocomplete, ext::string);
    DEFINE_SETTER(enctype, ext::string);
    DEFINE_SETTER(encoding, ext::string);
    DEFINE_SETTER(method, ext::string);
    DEFINE_SETTER(no_validate, ext::boolean);
    DEFINE_SETTER(target, ext::string);
    DEFINE_SETTER(rel, ext::string);

public cpp_operators:
    auto operator[](ext::string_view index) -> html_element*& override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FORM_ELEMENT_HPP
