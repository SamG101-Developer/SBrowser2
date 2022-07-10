#ifndef SBROWSER2_ENVIRONMENT_INITIALIZATION_HPP
#define SBROWSER2_ENVIRONMENT_INITIALIZATION_HPP

#include <memory>
#include <iostream>

#include <javascript/environment/environment_module.hpp>
#include <javascript/interop/automatic_object_conversions/expose_v8_conversions_to_context.hpp>

#include <v8-context.h>
#include <v8-initialization.h>
#include <v8-isolate.h>
#include <v8-platform.h>
#include <libplatform/libplatform.h>


namespace javascript::environment {
    auto initialize_v8_engine(
            char** argv)
            -> int;

    auto create_new_isolate()
            -> v8::Isolate*;

    auto create_new_context(
            v8::Isolate* isolate,
            module_t module_type)
            -> v8::Persistent<v8::Context>&;

    auto execute(
            v8::Isolate* isolate,
            const v8::Persistent<v8::Context>& persistent_context,
            const char* code)
            -> void;

    auto dispose_isolate(
            v8::Isolate* isolate)
            -> void;

    auto dispose_v8_engine()
            -> int;
}


std::unique_ptr<v8::Platform> platform;


auto javascript::environment::initialize_v8_engine(char** argv) -> int
{
    // initialize the icu default location and the external startup data
    v8::V8::InitializeICUDefaultLocation(argv[0]);
    v8::V8::InitializeExternalStartupData(argv[0]);

    // initialize the platform
    platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.get());

#ifdef V8_SANDBOX
    // initialize the sandbox if it is configured for use
    if (not v8::V8::InitializeSandbox())
    {
        std::cout << "Error initializing V8 Snadbox" << std::endl;
        return 1
    }
#endif

    // initialize v8
    v8::V8::Initialize();
    return 0;
}


inline auto javascript::environment::create_new_isolate() -> v8::Isolate*
{
    // create the create_params object for the array buffer allocator
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();

    // create a new isolate with the create_params object
    auto* isolate = v8::Isolate::New(create_params);
    return isolate;
}


inline auto javascript::environment::create_new_context(v8::Isolate* isolate, module_t module_type) -> v8::Persistent<v8::Context>&
{
    // create the isolate_ and handle_scope
    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope handle_scope(isolate);

    // create a local context from the isolate and set the module as the global object
    auto& persistent_context = interop::expose(isolate, module_type);
    return persistent_context;
}


inline auto javascript::environment::execute(v8::Isolate* isolate, const v8::Persistent<v8::Context>& persistent_context, const char* code) -> void
{
    // create the isolate_scope, handle_scope and context_scope
    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope handle_scope(isolate);
    v8::Local<v8::Context> local_context = v8::Local<v8::Context>::New(isolate, persistent_context);
    const v8::Context::Scope context_scope(local_context);

    {
        // create the source and script (from compiling the source), and run the script in the local context
        const v8::Local<v8::String> source = v8::String::NewFromUtf8(isolate, code).ToLocalChecked();
        const v8::Local<v8::Script> script = v8::Script::Compile(local_context, source).ToLocalChecked();
        const v8::Local<v8::Value>  result = script->Run(local_context).ToLocalChecked();

        // get the output and write it to console
        auto output = v8::String::Utf8Value(isolate, result);
        std::cout << "Result: " << *output << std::endl;
    }
}


inline auto javascript::environment::dispose_isolate(v8::Isolate* isolate) -> void
{
    // delete the array buffer allocator for the isolate and displose the isolate instance
    delete isolate->GetArrayBufferAllocator();
    isolate->Dispose();
}


auto javascript::environment::dispose_v8_engine() -> int
{
    // shutdown the platform, dispose the platform, and dispose v8
    v8::V8::Dispose();
    v8::V8::DisposePlatform();
    return 0;
}


#endif //SBROWSER2_ENVIRONMENT_INITIALIZATION_HPP
