#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_GLOBAL_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_GLOBAL_HPP


namespace web_assembly::js {class global;}

#include INCLUDE_INNER_TYPES(web_assembly_js)


class web_assembly::js::global
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(global);
    global() = default;
    global(detail::global_descriptor_t&& descriptor, const ext::any& value = nullptr);

private js_methods:
    auto value_of() -> ext::any;

private js_properties:
    ext::property<ext::any> value;

private js_properties:
    DEFINE_CUSTOM_GETTER(value);
    DEFINE_CUSTOM_SETTER(value);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_GLOBAL_HPP
