#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SELECT_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SELECT_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "ext/vector_like.ixx"
namespace html::elements {class html_select_element;}
namespace html::elements {class html_select_element_private;}

#include INCLUDE_INNER_TYPES(html)
namespace dom::nodes {class node;}
namespace html::elements {class html_form_element;}


class html::elements::html_select_element
        : public html_element
        , public ext::vector_like_linked<detail::option_like_element_t>
{
public constructors:
    DOM_CTORS(html_select_element);
    MAKE_PIMPL(html_select_element);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(autocomplete, ext::string_view);
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(value, ext::string);
    DEFINE_GETTER(disabled, ext::boolean);
    DEFINE_GETTER(multiple, ext::boolean);
    DEFINE_GETTER(required, ext::boolean);
    DEFINE_GETTER(form, html_form_element*);
    DEFINE_GETTER(size, ext::number<ulong>);
    DEFINE_GETTER(type, ext::string);
    DEFINE_GETTER(selected_index, ext::number<long>);
    DEFINE_GETTER(options, ext::vector_span<detail::option_like_element_t>);
    DEFINE_GETTER(selected_options, ext::vector_span<html_element*>);
    DEFINE_GETTER(labels, ext::vector_span<dom::nodes::node*>);

    DEFINE_SETTER(autocomplete, ext::string);
    DEFINE_SETTER(name, ext::string);
    DEFINE_SETTER(value, ext::string);
    DEFINE_SETTER(disabled, ext::boolean);
    DEFINE_SETTER(multiple, ext::boolean);
    DEFINE_SETTER(required, ext::boolean);
    DEFINE_SETTER(size, ext::number<ulong>);
    DEFINE_SETTER(selected_index, ext::number<long>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SELECT_ELEMENT_HPP
