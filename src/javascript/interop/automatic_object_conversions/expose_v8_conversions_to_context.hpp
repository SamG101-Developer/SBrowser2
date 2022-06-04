#ifndef SBROWSER2_EXPOSE_V8_CONVERSIONS_TO_CONTEXT_HPP
#define SBROWSER2_EXPOSE_V8_CONVERSIONS_TO_CONTEXT_HPP

#include <memory>

#include <ext/string.hpp>
#include <javascript/environment/environment_module.hpp>
#include <javascript/interop/manual_primitive_conversions/convert_string.hpp>

#include <v8-context.h>
#include <v8-isolate.h>
#include <v8-local-handle.h>
#include <v8-persistent-handle.h>
#include <v8-primitive.h>

#include <v8pp/class.hpp>
#include <v8pp/module.hpp>

namespace javascript::interop {auto expose(v8::Isolate* isolate, environment::module_t module_type) -> v8::Persistent<v8::Context>&;}


class A{
public:
    A(int a): m_a(a), m_b(nullptr) {};
    int m_a;
    std::shared_ptr<A> m_b;
    int double_a() {return m_a * 2;}
};


class console
{
public:
    auto static print(ext::string string) -> void {std::cout << string << std::endl;}
};


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
            v8_module.class_("A", v8pp::class_<A, v8pp::shared_ptr_traits>{isolate}
                .ctor<int>()
                .var("a_int", &A::m_a)
                .var("a_ptr", &A::m_b)
                .function("doubleA", &A::double_a));

            v8_module.class_("Console", v8pp::class_<console>{isolate}
                .function("print", &console::print));
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
