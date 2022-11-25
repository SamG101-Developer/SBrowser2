#ifndef SBROWSER2_SRC_JAVASCRIPT_ECMA_SPEC_262_7_ABSRACT_OPERATIONS_7_3_OPERATIONS_ON_OBJECTS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_ECMA_SPEC_262_7_ABSRACT_OPERATIONS_7_3_OPERATIONS_ON_OBJECTS_HPP

#include "2.hpp"

#include <v8-forward.h>


namespace js::ecma
{
    /* 7.3.02 */ auto Get(v8::Local<v8::Object> O, v8::Local<v8::Value> P) -> v8::Local<v8::Value>;
    /* 7.3.03 */ auto GetV(v8::Local<v8::Value> V, v8::Local<v8::Symbol> P) -> v8::Local<v8::Value>;
    /* 7.3.05 */ auto CreateDataProperty(v8::Local<v8::Object> O, v8::Local<v8::String> P, v8::Local<v8::Value> V);
    /* 7.3.11 */ auto GetMethod(v8::Local<v8::Value> V, v8::Local<v8::Symbol> P) -> v8::Local<v8::Value>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_ECMA_SPEC_262_7_ABSRACT_OPERATIONS_7_3_OPERATIONS_ON_OBJECTS_HPP
