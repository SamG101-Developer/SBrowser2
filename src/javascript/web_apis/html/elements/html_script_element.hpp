#ifndef SBROWSER2_HTML_SCRIPT_ELEMENT_HPP
#define SBROWSER2_HTML_SCRIPT_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_script_element;}

#include "ext/variant.hpp"
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(referrer_policy)


class html::elements::html_script_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_script_element);
    html_script_element();
    ~html_script_element() override;

public js_methods:
    static auto supports(ext::string_view type) -> ext::boolean;

public js_properties:
    ext::property<ext::string> src;
    ext::property<ext::string> type;
    ext::property<ext::boolean> no_module;
    ext::property<ext::boolean> async;
    ext::property<ext::boolean> defer;
    ext::property<ext::string> cross_origin;
    ext::property<ext::string> text;
    ext::property<ext::string> integrity;
    ext::property<referrer_policy::detail::referrer_policy_t> referrer_policy;
    ext::property<ext::string> blocking;

private cpp_properties:
    dom::nodes::document* m_parser_document;
    dom::nodes::document* m_preparation_document;
    ext::boolean m_force_async;
    ext::boolean m_from_external_file;
    ext::boolean m_ready_to_be_parser_executed;
    ext::boolean m_already_started;
    ext::boolean m_delaying_load_event;
    ext::variant<ext::string, std::unique_ptr<detail::script_t>> m_result;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(async);
    DEFINE_CUSTOM_GETTER(text);

    DEFINE_CUSTOM_SETTER(async);
    DEFINE_CUSTOM_SETTER(text);
};


#endif //SBROWSER2_HTML_SCRIPT_ELEMENT_HPP
