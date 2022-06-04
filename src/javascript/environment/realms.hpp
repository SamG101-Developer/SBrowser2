#ifndef SBROWSER2_REALMS_HPP
#define SBROWSER2_REALMS_HPP

namespace javascript::environment::realms {class realm;}
namespace web_apis {class dom_object;}

#include <ext/keywords.hpp>
#include <ext/string.hpp>

#include <v8-context.h>
#include <v8-isolate.h>
#include <v8-persistent-handle.h>

#include <v8pp/convert.hpp>


/*
 * Naming from ECMAScript to v8
 *   - agent           -> v8::Isolate*
 *   - realm           -> v8::Local<v8::Context>
 *   - global_object   -> v8::Local<v8::Object> (v8::Context::GlobalObject)
 *   - settings_object ->
 */


class javascript::environment::realms::realm
{
public constructors:
    explicit realm(v8::Isolate* isolate, v8::Persistent<v8::Context>& persistent_context) : m_context(v8::Local<v8::Context>::New(isolate, persistent_context)) {};

public cpp_static_methods:
    static auto relevant_realm(web_apis::dom_object* object) -> realm;
    static auto surrounding_realm(web_apis::dom_object* object) -> realm;
    static auto current_realm(web_apis::dom_object* object) -> realm;
    static auto entry_realm(web_apis::dom_object* object) -> realm;
    static auto incumbent_realm(web_apis::dom_object* object) -> realm;

public cpp_methods:
    template <typename T> auto get(ext::string&& attribute_name) const -> T;
    template <typename T> auto set(ext::string&& attribute_name, T new_value) -> void;
    template <typename T> auto global_object() -> T;
    auto settings_object();

private cpp_properties:
    v8::Local<v8::Context> m_context;
};


template <typename T>
inline auto javascript::environment::realms::realm::get(ext::string&& attribute_name) const -> T
{
    // save the v8 isolate, convert the attribute name into a v8 string, and get the object from the global object
    auto v8_isolate        = m_context->GetIsolate();
    auto v8_attribute_name = v8pp::convert<ext::string>::to_v8(v8_isolate, std::forward<ext::string>(attribute_name));
    auto v8_object         = m_context->Global()->Get(m_context, v8_attribute_name).ToLocalChecked();

    // convert the v8 object into a cpp object
    auto cpp_object = v8pp::convert<T>::from_v8(v8_isolate, v8_object);
    return cpp_object;
}


template <typename T>
inline auto javascript::environment::realms::realm::set(ext::string&& attribute_name, T new_value) -> void
{
    // save the v8 isolate, convert the attribute name into a v8 string, and convert the cpp new value into a v8 object
    auto v8_isolate        = m_context->GetIsolate();
    auto v8_attribute_name = v8pp::convert<ext::string>::to_v8(v8_isolate, std::forward<ext::string>(attribute_name));
    auto v8_new_value      = v8pp::convert<T>::to_v8(v8_isolate, new_value);

    // set the object's value into the global object
    m_context->Global()->Set(m_context, v8_attribute_name, v8_new_value);
}


template <typename T>
auto javascript::environment::realms::realm::global_object() -> T
{
    // save the v8 isolate, get the v8 global object proxy and the true v8 global object
    auto v8_isolate             = m_context->GetIsolate();
    auto v8_global_object_proxy = m_context->Global();
    auto v8_global_object_inner = v8_global_object_proxy->Get(m_context, v8::String::NewFromUtf8(v8_isolate, "Global").ToLocalChecked());

    // convert the true v8 global object into the cpp global object (ie dom::nodes::window)
    auto cpp_global_object = v8pp::convert<T>::from_v8(v8_isolate, v8_global_object_inner);
    return cpp_global_object;
}

#endif //SBROWSER2_REALMS_HPP
