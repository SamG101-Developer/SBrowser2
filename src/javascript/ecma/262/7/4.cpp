#include "4.hpp"

#include "javascript/ecma/262/7/3.hpp"

#include <v8-local-handle.h>
#include <v8-forward.h>
#include <v8-function.h>
#include <v8-isolate.h>
#include <v8-template.h>


auto js::ecma::GetIterator(v8::Local<v8::Object> obj, IteratorHint hint, v8::Local<v8::Function> method) -> IteratorRecord
{
    decltype(auto) isolate = v8::Isolate::GetCurrent();
    auto context = isolate->GetCurrentContext();

    if (method.IsEmpty())
    {
        if (hint == IteratorHint::kAsync)
            method = GetMethod(obj, v8::Symbol::GetIterator(isolate));
        if (method->IsUndefined())
        {
            auto sync_method = GetMethod(obj, v8::Symbol::GetIterator(isolate));
            auto sync_iterator_record = GetIterator(obj, IteratorHint::kSync, sync_method);
            return CreateAsyncFromSyncIterator(sync_iterator_record);
        }
    }

    else
    {
        method = GetMethod(obj, v8::Symbol::GetIterator(isolate));
    }

    auto iterator = Call(method, obj);
    // TODO
}


auto js::ecma::IteratorNext(js::ecma::IteratorRecord& iterator_record, v8::Local<v8::Value> V) -> v8::Local<v8::Object>
{
    decltype(auto) isolate = v8::Isolate::GetCurrent();
    auto context = isolate->GetCurrentContext();

    auto result = V.IsEmpty()
            ? Call(iterator_record.NextMethod, iterator_record.Iterator)
            : Call(iterator_record.NextMethod, iterator_record.Iterator, V);

    if (!result->IsObject())
        isolate->ThrowException(v8pp::to_v8(isolate, "Next iterator must be n Object"));

    return result.ToObject();
}


auto js::ecma::IteratorComplete(v8::Local<v8::Object> iterator_result) -> v8::Local<v8::Boolean>
{
    decltype(auto) isolate = v8::Isolate::GetCurrent();
    return ToBoolean(Get(iterator_result, v8pp::to_v8(isolate, "done")))
}

