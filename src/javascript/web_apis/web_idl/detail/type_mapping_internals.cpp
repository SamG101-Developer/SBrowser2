#include "type_mapping_internals.hpp"

#include "dom/detail/observer_internals.hpp"
#include "v8-promise.h"

#include <v8-internal.h>
#include <v8-isolate.h>
#include <v8-object.h>

#include <v8pp/convert.hpp>


template <typename T>
auto web_idl::detail::create_promise(v8::Local<v8::Context> realm) -> ext::promise<T>
{
    auto js_promise = v8::Promise::New(realm->GetIsolate());
    return convert<ext::promise<T>>(js_promise);
}


template <typename T>
auto web_idl::detail::create_resolved_promise(T&& x, v8::Local<v8::Context> realm) -> ext::promise<T>
{
    auto js_value = v8pp::to_v8(realm->GetIsolate(), std::forward<T>(x));
    auto js_promise_resolver = v8::Promise::Resolver::New(realm).ToLocalChecked();
    js_promise_resolver->Resolve(realm, js_value);
    return convert<ext::promise<T>>(realm->GetIsolate(), js_promise_resolver->GetPromise());
}


template <typename T>
auto web_idl::detail::create_rejected_promise(T&& reason, v8::Local<v8::Context> realm) -> ext::promise<T>
{
    auto js_value = v8pp::to_v8(realm->GetIsolate(), std::forward<T>(reason));
    auto js_promise_resolver = v8::Promise::Resolver::New(realm).ToLocalChecked();
    js_promise_resolver->Reject(realm, js_value);
    return convert<ext::promise<T>>(realm->GetIsolate(), js_promise_resolver->GetPromise());
}


template <typename T>
auto web_idl::detail::resolve_promise(ext::promise<T>& promise, v8::Local<v8::Context> realm, ext::optional<T>&& x) -> void
{
    auto js_promise = v8pp::to_v8(realm->GetIsolate(), promise).template As<v8::Promise::Resolver>();
    auto js_value = x.has_value() ? v8pp::to_v8(realm->GetIsolate(), std::forward<T>(x)) : v8::Null(realm->GetIsolate());
    js_promise.Resolve(realm, js_value);
}


template <typename T, typename U>
auto web_idl::detail::reject_promise(ext::promise<T>& promise, v8::Local<v8::Context> realm, U&& reason) -> void
{
    auto js_promise = v8pp::to_v8(realm->GetIsolate(), promise).template As<v8::Promise::Resolver>();
    auto js_value = v8pp::to_v8(realm, std::forward<U>(reason));
    js_promise.Reject(realm, js_value);
}


template <typename T, ext::callable F0, ext::callable F1>
auto web_idl::detail::react(ext::promise<T>& promise, v8::Local<v8::Context> realm, ext::optional<F0>&& fullfilled_steps, ext::optional<F1>&& rejected_steps) -> void
{
    auto on_fullfilled_steps =
            [realm, fullfilled_steps = std::move(fullfilled_steps)](v8::Local<v8::Object> V) -> T
            {
        auto cpp_value = v8pp::from_v8<T>(realm->GetIsolate(), V);
        constexpr_return_if (ext::type_is<T COMMA void>) fullfilled_steps(cpp_value);
        else return_if(fullfilled_steps.has_value()) fullfilled_steps(cpp_value);
        return V;
            };
    auto on_fullfilled = v8::Function::New(realm, std::move(on_fullfilled_steps));

    auto on_rejected_steps =
            [realm, rejected_steps = std::move(rejected_steps)](v8::Local<v8::Object> R)
            {
        auto cpp_value = v8pp::from_v8<ext::any>(realm->GetIsolate(), R);
        return_if (rejected_steps.has_value()) rejected_steps(cpp_value);
        return create_rejected_promise(std::move(cpp_value), realm);
            };
    auto on_rejected = v8::Function::New(realm, std::move(on_rejected_steps));

    return js::ecma::perform_promise_then(promise, on_fullfilled, on_rejected);
}


template <typename T, ext::callable F0, ext::callable F1>
auto web_idl::detail::wait_for_all(ext::vector_span<ext::promise<T>*> promises, v8::Local<v8::Context> realm, F0&& success_steps, F1&& failure_steps) -> void
{
    using namespace ext::literals;
    auto fulfilled_count = 0_n;
    auto rejected = ext::boolean::FALSE_();

    auto rejection_handler_steps =
            [&rejected, failure_steps = std::forward<F1>(failure_steps)]<typename U>(U&& arg) mutable
            {
        return_if (rejected);
        rejected = true;
        failure_steps(std::forward<U>(arg));
            };

    auto rejection_handler = v8::Function::New(realm, std::move(rejection_handler_steps));
    auto total = promises.size();
    if (total == 0)
    {
        dom::detail::queue_microtask(std::move(success_steps));
        return;
    }

    auto index = 0_n;
    auto result = ext::vector<T>{}; // TODO : fill with default values
    for (const auto& promise: promises)
    {
        auto promise_index = index;
        auto fulfillment_handler_steps =
                [total, &result, &promise_index, &fulfilled_count, success_steps = std::forward<F1>(success_steps)]<typename U>(U&& arg) mutable
                {
            result[promise_index] = std::forward<U>(arg);
            fulfilled_count += 1;
            if (fulfilled_count == total) success_steps(result);
                };

        auto fulfillment_handler = v8::Function::New(realm, fulfillment_handler_steps);
        js::ecma::perform_promise_then(promise, std::move(fulfillment_handler), std::move(rejection_handler));
        index += 1;
    }
}


template <typename T>
auto web_idl::detail::get_promise_for_waiting_for_all(ext::vector_span<ext::promise<T>*> promises, v8::Local<v8::Context> realm) -> ext::promise<T>
{
    auto js_promise = v8::Promise::Resolver::New(realm);
    auto promise = convert<ext::promise<T>>(js_promise);
    auto success_steps = BIND_FRONT(resolve_promise, promise);
    auto failure_steps = BIND_FRONT(reject_promise, promise);
    wait_for_all(promises, std::move(success_steps), std::move(failure_steps));
    return promise;
}
