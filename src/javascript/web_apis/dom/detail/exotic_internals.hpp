#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_DETAIL_EXOTIC_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_DETAIL_EXOTIC_INTERNALS_HPP

#include "ext/boolean.ixx"
#include "ext/map.ixx"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include <v8-forward.h>
#include <v8-object.h>


namespace dom::detail
{
    template <typename T>
    auto cross_origin_properties(
            T* object)
            -> v8::Local<v8::Array>;

    auto cross_origin_property_fallback(
            ext::string_view property)
            -> v8::Local<v8::PropertyDescriptor>;

    auto is_platform_object_same_origin(
            v8::Local<v8::Object> object1,
            v8::Local<v8::Object> object2)
            -> ext::boolean;

    auto cross_origin_get_own_property_helper(
            v8::Local<v8::Object> object,
            v8::Local<v8::PropertyDescriptor> property)
            -> auto; // TODO

    auto cross_origin_get(
            v8::Local<v8::Object> object,
            v8::Local<v8::PropertyDescriptor> property,
            v8::Local<v8::Function> receiver)
            -> auto; // TODO

    auto cross_origin_set(
            v8::Local<v8::Object> object,
            v8::Local<v8::PropertyDescriptor> property,
            v8::Local<v8::Value> value,
            v8::Local<v8::Function> receiver)
            -> auto; // TODO

    auto cross_origin_own_property_keys(
            v8::Local<v8::Object> object)
            -> v8::Local<v8::Array>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_DETAIL_EXOTIC_INTERNALS_HPP
