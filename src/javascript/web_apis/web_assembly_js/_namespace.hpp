#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS__NAMESPACE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS__NAMESPACE_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include <future>
#include <v8-forward.h>
#include USE_INNER_TYPES(web_assembly_js)
namespace fetch {class response;}
namespace web_assembly::js {class instance;}
namespace web_assembly::js {class module;}


namespace web_assembly::js
{
    auto validate(
            v8::Local<v8::ArrayBuffer> bytes)
            -> ext::boolean;

    auto compile(
            v8::Local<v8::ArrayBuffer> bytes)
            -> std::promise<module>;

    auto instantiate(
            v8::Local<v8::ArrayBuffer> bytes,
            const ext::any& import_object = nullptr)
            -> std::promise<detail::web_assembly_instantiated_source_t>;

    auto instantiate(
            module* module_object,
            const ext::any& import_object = nullptr)
            -> std::promise<instance>;

    /* WEB_ASSEMBLY WEB */
    auto compile_streaming(
            std::promise<fetch::response*> source)
            -> std::promise<module*>;

    auto instantiate_streaming(
            std::promise<fetch::response*> source,
            const ext::any& import_object)
            -> std::promise<detail::web_assembly_instantiated_source_t>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS__NAMESPACE_HPP