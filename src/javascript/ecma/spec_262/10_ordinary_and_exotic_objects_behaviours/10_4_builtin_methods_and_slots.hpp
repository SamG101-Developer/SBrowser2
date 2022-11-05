#ifndef SBROWSER2_SRC_JAVASCRIPT_ECMA_SPEC_262_10_ORDINARY_AND_EXOTIC_OBJECTS_BEHAVIOURS_10_4_BUILTIN_METHODS_AND_SLOTS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_ECMA_SPEC_262_10_ORDINARY_AND_EXOTIC_OBJECTS_BEHAVIOURS_10_4_BUILTIN_METHODS_AND_SLOTS_HPP

#include <v8-object.h>

namespace javascript::ecma
{
    /* 10.4.7.1 */ // v8::Object::SetPrototype(...)
    /* 10.4.7.2 */ auto SetImmutablePrototype(v8::Local<v8::Object> O, v8::Local<v8::Object> V) -> bool;
}


auto javascript::ecma::SetImmutablePrototype(
        v8::Local<v8::Object> O,
        v8::Local<v8::Object> V)
        -> bool
{
    auto C = O->GetPrototype();
    return V->SameValue(C);
}


#endif //SBROWSER2_SRC_JAVASCRIPT_ECMA_SPEC_262_10_ORDINARY_AND_EXOTIC_OBJECTS_BEHAVIOURS_10_4_BUILTIN_METHODS_AND_SLOTS_HPP
