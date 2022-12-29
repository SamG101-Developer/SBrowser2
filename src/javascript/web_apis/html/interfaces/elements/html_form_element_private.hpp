#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FORM_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FORM_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "html/elements/html_element_private.hpp"
#include "html/mixins/validatable_private.hpp"


DEFINE_PRIVATE_CLASS(html::elements, html_form_element)
        : html::elements::html_element_private
        , html::mixins::validatable_private
{
    ext::string accept_charset;
    ext::string action;
    ext::string autocomplete;
    ext::string enctype;
    ext::string method;
    ext::string name;
    ext::string no_validate;
    ext::string target;
    ext::string rel;

    ext::map<ext::string, html_element*> past_map;
    ext::boolean constructing_entry_list;
    ext::boolean firing_submission_events;
    ext::boolean locked_for_reset;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_FORM_ELEMENT_PRIVATE_HPP
