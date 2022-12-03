#ifndef SBROWSER2_SRC_JAVASCRIPT_ECMA_262_7_4_HPP
#define SBROWSER2_SRC_JAVASCRIPT_ECMA_262_7_4_HPP

#include "ext/boolean.ixx"

#include "ext/optional.hpp"
#include "javascript/ecma/262/7/3.hpp"
#include <v8-forward.h>


namespace js::ecma
{
    struct IteratorRecord;
    enum class IteratorHint {kSync, kAsync};

    /* 7.4.02 */ auto GetIterator(v8::Local<v8::Object> obj, IteratorHint hint = IteratorHint::kSync, v8::Local<v8::Function> method = v8::Function::New()) -> IteratorRecord;
    /* 7.4.03 */ auto IteratorNext(IteratorRecord& iterator_record, v8::Local<v8::Value> V = v8::Object::New()) -> v8::Local<v8::Object>;
    /* 7.4.04 */ auto IteratorComplete(v8::Local<v8::Object> iterator_result) -> v8::Local<v8::Boolean>;
}


struct js::ecma::IteratorRecord
{
    v8::Local<v8::Object> Iterator;
    v8::Local<v8::Function> NextMethod;
    ext::boolean Done;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_ECMA_262_7_4_HPP
