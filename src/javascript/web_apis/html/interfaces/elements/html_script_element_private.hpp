#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SCRIPT_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SCRIPT_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "html/elements/html_element_private.hpp"

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(referrer_policy)


DEFINE_PRIVATE_CLASS(html::elements, html_script_element) : html::elements::html_element_private
{
    ext::string src;
    ext::string type;
    ext::boolean no_module;
    ext::boolean async;
    ext::boolean defer;
    html::detail::cross_origin_settings_attribute_t cross_origin;
    ext::string integrity;
    referrer_policy::detail::referrer_policy_t referrer_policy;
    ext::string blocking;

    std::observer_ptr<dom::nodes::document> parser_document;
    std::observer_ptr<dom::nodes::document> preparation_document;
    ext::boolean force_async;
    ext::boolean from_external_file;
    ext::boolean ready_to_be_parser_executed;
    ext::boolean already_started;
    ext::boolean delaying_load_event;
    ext::variant<ext::string, std::unique_ptr<detail::script_t>> result;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_SCRIPT_ELEMENT_PRIVATE_HPP
