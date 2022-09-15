#ifndef SBROWSER2_REALMS_2_HPP
#define SBROWSER2_REALMS_2_HPP

#include "ext/boolean.hpp"
#include "javascript/interop/manual_primitive_conversions/convert_boolean.hpp"
#include "javascript/interop/manual_primitive_conversions/convert_nullptr_t.hpp"
#include "javascript/interop/manual_primitive_conversions/convert_number.hpp"
#include "javascript/environment/environment_settings.hpp"

#include <v8-context.h>
#include <v8-isolate.h>
#include <v8-maybe.h>
#include <v8-object.h>
#include <v8-persistent-handle.h>
#include <v8pp/convert.hpp>


#define _JS_GLOBAL_OBJECT_FROM_REALM(type) \
    type##_realm->Global().As<v8::Object>()

#define _JS_SETTINGS_OBJECT_FROM_REALM(type) \
    type##_realm->Global()->Get(type##_realm, v8pp::to_v8(type##_agent, "[[Settings]]")).ToLocalChecked().As<v8::Object>()


#define JS_REALM_GET_CURRENT                                            \
    auto current_agent = v8::Isolate::GetCurrent();                     \
    auto current_realm = current_agent->GetCurrentContext();            \
    auto current_global_object = _JS_GLOBAL_OBJECT_FROM_REALM(current); \
    auto current_settings_object = _JS_SETTINGS_OBJECT_FROM_REALM(current)

#define JS_REALM_GET_ENTRY(object)                                                                    \
    JS_REALM_GET_CURRENT                                                                              \
    auto object ## _creation_realm = v8pp::to_v8(current_agent, object)->GetCreationContextChecked(); \
    auto object ## _creation_agent = creation_realm->GetIsolate();                                    \
    auto object ## _creation_global_object = _JS_GLOBAL_OBJECT_FROM_REALM(creation);                  \
    auto current_settings_object = _JS_SETTINGS_OBJECT_FROM_REALM(relevant)

#define JS_REALM_GET_IMPLIED                                            \
    auto implied_agent = v8::Isolate::GetCurrent();                     \
    auto implied_realm = implied_agent->GetCurrentContext();            \
    auto implied_global_object = _JS_GLOBAL_OBJECT_FROM_REALM(implied); \
    auto implied_settings_object = _JS_SETTINGS_OBJECT_FROM_REALM(implied)

#define JS_REALM_GET_INCUMBENT                                            \
    auto incumbent_agent = v8::Isolate::GetCurrent();                     \
    auto incumbent_realm = incumbent_agent->GetIncumbentContext();        \
    auto incumbent_global_object = _JS_GLOBAL_OBJECT_FROM_REALM(current); \
    auto incumbent_settings_object = _JS_SETTINGS_OBJECT_FROM_REALM(incumbent)

#define JS_REALM_GET_RELEVANT(object)                                                                                                                                                     \
    JS_REALM_GET_CURRENT;                                                                                                                                                                 \
    auto object ## _relevant_realm = v8pp::to_v8(current_agent, object).As<v8::Object>()->Get(current_realm, v8pp::to_v8(current_agent, "[[Realm]]")).ToLocalChecked().As<v8::Context>(); \
    auto object ## _relevant_agent = object ## _relevant_realm->GetIsolate();                                                                                                             \
    auto object ## _relevant_global_object = _JS_GLOBAL_OBJECT_FROM_REALM(object ## _relevant).As<v8::Object>();                                                                          \
    auto object ## _relevant_settings_object = _JS_SETTINGS_OBJECT_FROM_REALM(object ## _relevant)

#define JS_REALM_GET_SURROUNDING(object) /* Same as relevant */                                                                                                                              \
    JS_REALM_GET_CURRENT;                                                                                                                                                                    \
    auto object ## _surrounding_realm = v8pp::to_v8(current_agent, object).As<v8::Object>()->Get(current_realm, v8pp::to_v8(current_agent, "[[Realm]]")).ToLocalChecked().As<v8::Context>(); \
    auto object ## _surrounding_agent = object ## _surrounding_realm->GetIsolate();                                                                                                          \
    auto object ## _surrounding_global_object = _JS_GLOBAL_OBJECT_FROM_REALM(object ## _surrounding).As<v8::Object>();                                                                       \
    auto object ## _surrounding_settings_object = _JS_SETTINGS_OBJECT_FROM_REALM(object ## _surrounding)

#define JS_REALM_GET_ASSOCIATED(object)                                           \
    JS_REALM_GET_RELEVANT(object);                                                \
    auto object ## _associated_agent = object ## _relevant_agent;                 \
    auto object ## _associated_realm = object ## _relevant_realm;                 \
    auto object ## _associated_global_object = object ## _relevant_global_object; \
    auto object ## _associated_settings_object = object ## _relevant_settings_object

#define JS_REALM_GET_CREATION(object)                                                                            \
    auto object ## _creation_realm = v8pp::to_v8(v8::Isolate::GetCurrent(), object)->CreationContext();          \
    auto object ## _creation_agent = object ## _creation_realm->GetIsolate();                                    \
    auto object ## _creation_global_object = _JS_GLOBAL_OBJECT_FROM_REALM(object ## _creation).As<v8::Object>(); \
    auto object ## _creation_settings_object = _JS_SETTINGS_OBJECT_FROM_REALM(object ## _creation)


//#undef _JS_GLOBAL_OBJECT_FROM_REALM
//#undef _JS_SETTINGS_OBJECT_FROM_REALM

namespace javascript::environment::realms_2
{
    auto has(
            v8::Local<v8::Object> global,
            ext::string_view cpp_attribute)
            -> ext::boolean;

    template <typename T>
    auto get(
            v8::Local<v8::Object> global,
            ext::string_view cpp_attribute)
            -> T;

    template <typename T>
    auto set(
            v8::Local<v8::Object> global,
            ext::string_view cpp_attribute,
            T cpp_value)
            -> ext::boolean;
}


// TODO : isolate as variables in methods (reduce code duplication with calling ...->GetIsolate()
auto javascript::environment::realms_2::has(v8::Local<v8::Object> global, ext::string_view cpp_attribute) -> ext::boolean
{
    auto v8_private_attribute = v8::Private::New(global->GetIsolate(), v8pp::to_v8(global->GetIsolate(), cpp_attribute).As<v8::String>());
    auto v8_exists = global->HasPrivate(global->GetIsolate()->GetCurrentContext(), v8_private_attribute).FromJust();
    auto cpp_exists = v8_exists;
    return cpp_exists;
}


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
