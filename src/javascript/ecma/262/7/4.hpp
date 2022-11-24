#ifndef SBROWSER2_SRC_JAVASCRIPT_ECMA_262_7_4_HPP
#define SBROWSER2_SRC_JAVASCRIPT_ECMA_262_7_4_HPP

#include "ext/boolean.hpp"
#include "ext/functional.hpp"
#include "ext/optional.hpp"
#include "javascript/ecma/262/7/3.hpp"

#include <v8-forward.h>
#include <v8-function.h>
#include <v8-isolate.h>
#include <v8-template.h>

namespace js::ecma
{
    struct IteratorRecord;
    enum class IteratorHint {kSync, kAsync};

    /* 7.4.02 */ auto GetIterator(v8::Local<v8::Object> obj, ext::optional<IteratorHint> hint_ = ext::nullopt, ext::optional<v8::Local<v8::Function>> method_ = ext::nullopt) -> IteratorRecord;
}


struct js::ecma::IteratorRecord
{
    v8::Local<v8::Object> iterator;
    v8::Local<v8::Function> next_method;
    ext::boolean done;
};


auto js::ecma::GetIterator(v8::Local<v8::Object> obj, ext::optional<IteratorHint> hint_, ext::optional<v8::Local<v8::Function>> method_) -> IteratorRecord
{
    decltype(auto) isolate = v8::Isolate::GetCurrent();
    auto context = isolate->GetCurrentContext();

    decltype(auto) hint = hint_.has_value() ? *hint_ : IteratorHint::kSync;
    v8::Local<v8::Function> method;

    if (!method_.has_value())
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


#endif //SBROWSER2_SRC_JAVASCRIPT_ECMA_262_7_4_HPP
