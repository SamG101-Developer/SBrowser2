#ifndef SBROWSER2_EXPOSE_V8_CONVERSIONS_TO_CONTEXT_HPP
#define SBROWSER2_EXPOSE_V8_CONVERSIONS_TO_CONTEXT_HPP

#include <memory>

#include <javascript/environment/environment_module.hpp>

#include <javascript/interop/automatic_object_conversions/cpp_object_to_v8.hpp>
#include <javascript/interop/manual_primitive_conversions/convert_any.hpp>
#include <javascript/interop/manual_primitive_conversions/convert_boolean.hpp>
#include <javascript/interop/manual_primitive_conversions/convert_map.hpp>
#include <javascript/interop/manual_primitive_conversions/convert_map_like.hpp>
#include <javascript/interop/manual_primitive_conversions/convert_number_float.hpp>
#include <javascript/interop/manual_primitive_conversions/convert_number_integer.hpp>
#include <javascript/interop/manual_primitive_conversions/convert_optional.hpp>
#include <javascript/interop/manual_primitive_conversions/convert_property.hpp>
#include <javascript/interop/manual_primitive_conversions/convert_set.hpp>
#include <javascript/interop/manual_primitive_conversions/convert_string.hpp>
#include <javascript/interop/manual_primitive_conversions/convert_vector.hpp>
#include <javascript/interop/manual_primitive_conversions/convert_vector_like.hpp>

#include <web_apis/dom/events/event.hpp>

#include <web_apis/dom/nodes/event_target.hpp>

#include <v8-context.h>
#include <v8-isolate.h>
#include <v8-local-handle.h>
#include <v8-persistent-handle.h>
#include <v8-primitive.h>

#include <v8pp/class.hpp>
#include <v8pp/module.hpp>

namespace javascript::interop {auto expose(v8::Isolate* isolate, environment::module_t module_type) -> v8::Persistent<v8::Context>&;}


inline auto javascript::interop::expose(v8::Isolate* isolate, environment::module_t module_type) -> v8::Persistent<v8::Context>&
{
    // create the context objects and create a module for the classes ie the Window module
    v8pp::module v8_module{isolate};
    auto local_context = v8::Context::New(isolate);
    auto static persistent_context = v8::Persistent<v8::Context>{isolate, local_context};
    local_context->Enter();

    // different classes are exposed to different modules, and assign the module name
    switch (module_type)
    {
        case (environment::module_t::WINDOW):
        {
            v8_module.class_("Event", cpp_object_to_v8<dom::events::event>(isolate));
            v8_module.class_("EventTarget", cpp_object_to_v8<dom::nodes::event_target>(isolate));

            local_context->Global()->SetPrivate(local_context, v8::Private::New(isolate, v8pp::to_v8(isolate, "type")), v8pp::to_v8(isolate, "Window"));
        }

        case (environment::module_t::WORKER):
        {
        }

        case (environment::module_t::WORKLET):
        {
        }
    }

    local_context->Global()->Set(local_context, v8pp::convert<std::string>::to_v8(isolate, "Window"), v8_module.new_instance());
    return persistent_context;
}

#endif //SBROWSER2_EXPOSE_V8_CONVERSIONS_TO_CONTEXT_HPP
