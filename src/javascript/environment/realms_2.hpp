#ifndef SBROWSER2_REALMS_2_HPP
#define SBROWSER2_REALMS_2_HPP

#include <v8-context.h>
#include <v8-isolate.h>
#include <v8-maybe.h>
#include <v8-persistent-handle.h>

#include <javascript/interop/manual_primitive_conversions/convert_nullptr_t.hpp>
#include <javascript/interop/manual_primitive_conversions/convert_string.hpp>
#include <v8pp/convert.hpp>


#define _JS_GLOBAL_OBJECT_FROM_REALM(type) \
    type##_realm->Global()->Get(type##_realm, v8pp::to_v8(type##_agent, "Global")).ToLocalChecked().As<v8::Object>()

#define JS_REALM_GET_CURRENT                                 \
    auto current_agent = v8::Isolate::GetCurrent();          \
    auto current_realm = current_agent->GetCurrentContext(); \
    auto current_global_object = _JS_GLOBAL_OBJECT_FROM_REALM(current);

#define JS_REALM_GET_ENTRY(object)                                                         \
    JS_REALM_GET_CURRENT                                                                   \
    auto creation_realm = v8pp::to_v8(current_agent, object)->GetCreationContextChecked(); \
    auto creation_agent = creation_realm->GetIsolate();                                    \
    auto creation_global_object = _JS_GLOBAL_OBJECT_FROM_REALM(creation);

#define JS_REALM_GET_IMPLIED /* Same as current (unambiguous in spec) */ \
    auto implied_agent = v8::Isolate::GetCurrent();                      \
    auto implied_realm = implied_agent->GetCurrentContext();             \
    auto implied_global_object = _JS_GLOBAL_OBJECT_FROM_REALM(implied);

#define JS_REALM_GET_INCUMBENT                                     \
    auto incumbent_agent = v8::Isolate::GetCurrent();              \
    auto incumbent_realm = incumbent_agent->GetIncumbentContext(); \
    auto incumbent_global_object = _JS_GLOBAL_OBJECT_FROM_REALM(current);

#define JS_REALM_GET_RELEVANT(object)                                                                                                                                          \
    JS_REALM_GET_CURRENT                                                                                                                                                       \
    auto relevant_realm = v8pp::to_v8(current_agent, object).As<v8::Object>()->Get(current_realm, v8pp::to_v8(current_agent, "[[Realm]]")).ToLocalChecked().As<v8::Context>(); \
    auto relevant_agent = relevant_realm->GetIsolate();                                                                                                                        \
    auto relevant_global_object = _JS_GLOBAL_OBJECT_FROM_REALM(relevant).As<v8::Object>();

#define JS_REALM_GET_SURROUNDING(object) /* Same as relevant */                                                                                                                   \
    JS_REALM_GET_CURRENT                                                                                                                                                          \
    auto surrounding_realm = v8pp::to_v8(current_agent, object).As<v8::Object>()->Get(current_realm, v8pp::to_v8(current_agent, "[[Realm]]")).ToLocalChecked().As<v8::Context>(); \
    auto surrounding_agent = surrounding_realm->GetIsolate();                                                                                                                     \
    auto surrounding_global_object = _JS_GLOBAL_OBJECT_FROM_REALM(surrounding).As<v8::Object>();

#define JS_REALM_GET_ASSOCIATED(object)     \
    JS_REALM_GET_RELEVANT(object)           \
    auto associated_agent = relevant_agent; \
    auto associated_realm = relevant_realm; \
    auto associated_global_object = relevant_global_object;


namespace javascript::environment::realms_2 {template <typename T> auto get(v8::Local<v8::Object> global, ext::string_view cpp_attribute) -> T;}
namespace javascript::environment::realms_2 {template <typename T> auto set(v8::Local<v8::Object> global, ext::string_view cpp_attribute, T cpp_value) -> ext::boolean;}


template <typename T>
auto javascript::environment::realms_2::get(v8::Local<v8::Object> global, ext::string_view cpp_attribute) -> T
{
    auto v8_private_attribute = v8::Private::New(global->GetIsolate(), v8pp::to_v8(global->GetIsolate(), cpp_attribute).As<v8::String>());
    auto v8_value = global->GetPrivate(global->GetIsolate()->GetCurrentContext(), v8_private_attribute).ToLocalChecked();
    auto cpp_value = v8pp::from_v8<T>(global->GetIsolate(), v8_value);
    return cpp_value;
}


template <typename T>
auto javascript::environment::realms_2::set(v8::Local<v8::Object> global, ext::string_view cpp_attribute, T cpp_value) -> ext::boolean
{
    auto v8_private_attribute = v8::Private::New(global->GetIsolate(), v8pp::to_v8(global->GetIsolate(), cpp_attribute).As<v8::String>());
    auto v8_value = v8pp::to_v8(global->GetIsolate(), cpp_value);
    auto cpp_success = global->SetPrivate(global->GetIsolate()->GetCurrentContext(), v8_private_attribute, v8_value).FromJust();
    return cpp_success;
}


#endif //SBROWSER2_REALMS_2_HPP
