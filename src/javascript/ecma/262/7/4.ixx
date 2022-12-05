module;
#include <v8-forward.h>


export module js.ecma._262._7._4;
import ext.boolean;

export namespace js::ecma
{
    struct IteratorRecord;
    enum class IteratorHint {kSync, kAsync};

    /* 7.4.02 */ auto GetIterator(v8::Local<v8::Object> obj, IteratorHint hint = IteratorHint::kSync, v8::Local<v8::Function> method = v8::Null()) -> IteratorRecord;
    /* 7.4.03 */ auto IteratorNext(IteratorRecord& iterator_record, v8::Local<v8::Value> V = v8::Null()) -> v8::Local<v8::Object>;
    /* 7.4.04 */ auto IteratorComplete(v8::Local<v8::Object> iterator_result) -> v8::Local<v8::Boolean>;
}

export struct js::ecma::IteratorRecord
{
    v8::Local<v8::Object> Iterator;
    v8::Local<v8::Function> NextMethod;
    ext::boolean Done;
};
