#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_INSTANCE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_INSTANCE_HPP

#include "dom_object.hpp"
namespace web_assembly::js {class instance;}

namespace web_assembly::js {class module;}


class web_assembly::js::instance
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(instance);
    instance() = default;
    instance(module* module, const ext::any& import_object);

private js_properties:
    ext::property<ext::any> exports;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS_INSTANCE_HPP
