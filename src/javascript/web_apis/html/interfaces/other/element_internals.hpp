#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_ELEMENT_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_ELEMENT_INTERNALS_HPP


#include "html/mixins/validatable.hpp"
#include "aria/mixins/aria_mixin.hpp"
namespace html::other {class element_internals;}
namespace html::other {class element_internals_private;}

#include "ext/optional.ixx"

#include "ext/span.hpp"
namespace dom::nodes {class node;}
namespace dom::nodes {class shadow_root;}
namespace file_api {class file;}
namespace html::elements {class html_form_element;}
namespace xhr {class form_data;}


class html::other::element_internals
        : public virtual dom_object
        , public mixins::validatable
        , public aria::mixins::aria_mixin
{
public constructors:
    element_internals();
    MAKE_PIMPL(element_internals);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto set_form_value(
            ext::variant<file_api::file*, ext::string, xhr::form_data*> value,
            ext::variant<file_api::file*, ext::string, xhr::form_data*> state = u8"")
            -> void;

private js_properties:
    DEFINE_GETTER(shadow_root, dom::nodes::shadow_root*);
    DEFINE_GETTER(form, elements::html_form_element*);
    DEFINE_GETTER(labels, ext::vector_span<dom::nodes::node*>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_ELEMENT_INTERNALS_HPP
