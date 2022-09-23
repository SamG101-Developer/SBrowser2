#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_ELEMENT_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_ELEMENT_INTERNALS_HPP

#include "dom_object.hpp"
#include "html/mixins/validatable.hpp"
#include "aria/mixins/aria_mixin.hpp"
namespace html::other {class element_internals;}

#include "ext/optional.hpp"
#include "ext/variant.hpp"
namespace dom::nodes {class shadow_root;}
namespace file_api {class file;}
namespace html::elements {class html_form_element;}
namespace xhr {class form_data;}


class html::other::element_internals
        : public virtual dom_object
        , public mixins::validatable
        , public aria::mixins::aria_mixin
{
public js_methods:
    auto set_form_value(ext::variant<file_api::file*, ext::string, xhr::form_data*> value, ext::variant<file_api::file*, ext::string, xhr::form_data*> state = "") -> void;

private js_properties:
    ext::property<dom::nodes::shadow_root*> shadow_root_node;
    ext::property<elements::html_form_element*> form;
    ext::property<std::unique_ptr<ext::vector<dom::nodes::node*>>> labels;

private cpp_properties:
    std::unique_ptr<dom::nodes::node*> m_target_element;

private js_properties:
    DEFINE_CUSTOM_GETTER(shadow_root_node);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_ELEMENT_INTERNALS_HPP
