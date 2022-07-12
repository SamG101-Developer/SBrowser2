#ifndef SBROWSER2_REFLECTION_HPP
#define SBROWSER2_REFLECTION_HPP


#include "javascript/interop/annotations.hpp"

#define reflect_get_attribute_value(_object, _attribute, _attribute_t, _env_t)                            \
    [_env_t ## _agent, _env_t ## _realm](auto _cpp_object, auto _cpp_attribute)                           \
    {                                                                                                     \
        _attribute_t _cpp_attribute_value;                                                                \
        JS_BLOCK_ENTER                                                                                    \
            auto _js_object = v8pp::to_v8(_env_t ## _agent, _cpp_object);                                 \
            auto _js_attribute = v8pp::to_v8(_env_t ## _agent, _cpp_attribute);                           \
            auto _js_attribute_value = _js_object->Get(_env_t ## _realm, _js_attribute).ToLocalChecked(); \
            _cpp_attribute_value = v8pp::from_v8<_attribute_t>(_env_t ## _agent, _js_attribute_value);    \
        JS_BLOCK_EXIT                                                                                     \
                                                                                                          \
        return _cpp_attribute_value;                                                                      \
    }(_object, _attribute)

#define reflect_has_attribute_value(_object, _attribute, _env_t)                          \
    [_env_t ## _agent, _env_t ## _realm](auto _cpp_object, auto _cpp_attribute)           \
    {                                                                                     \
        ext::boolean _has_attribute;                                                      \
        JS_BLOCK_ENTER                                                                    \
            auto _js_object = v8pp::to_v8(_env_t ## _agent, _cpp_object);                 \
            auto _js_attribute = v8pp::to_v8(_env_t ## _agent, _cpp_attribute);           \
            _has_attribute = _js_object->Has(_env_t ## _realm, _js_attribute).FromJust(); \
        JS_BLOCK_EXIT                                                                     \
                                                                                          \
        return _has_attribute;                                                            \
    }(_object, _attribute)


#endif //SBROWSER2_REFLECTION_HPP
