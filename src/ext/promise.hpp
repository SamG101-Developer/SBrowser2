#ifndef SBROWSER2_SRC_EXT_PROMISE_HPP
#define SBROWSER2_SRC_EXT_PROMISE_HPP

#include "ext/boolean.hpp"
#include "ext/keywords.hpp"
#include <v8-isolate.h>
#include <v8-local-handle.h>
#include <v8-promise.h>


_EXT_BEGIN


template <typename ...Ts>
class promise
{
public:
    template <typename U>
    auto resolve(U&& value) -> promise<Ts...>&
    {m_v8_promise->Resolve(v8::Isolate::GetCurrent()->GetCurrentContext(), v8pp::to_v8(v8::Isolate::GetCurrent(), std::forward<U>(value))); return *this;};

    template <typename U>
    auto reject(U&& exception) -> promise<Ts...>&
    {m_v8_promise->Reject(v8::Isolate::GetCurrent()->GetCurrentContext(), v8pp::to_v8(v8::Isolate::GetCurrent(), std::forward<U>(exception))); return *this;}

    template <callable F0, callable F1>
    auto react(F0&& fulfilled_steps, F1&& rejected_steps = []{}) -> promise<Ts...>&;

    ext::boolean is_resolved = false;
    ext::boolean is_rejected = false;

private:
    v8::Local<v8::Promise::Resolver> m_v8_promise;
};


template <>
class promise<void>
{
public:
    auto resolve() -> promise<void>&
    {m_v8_promise->Resolve(v8::Isolate::GetCurrent()->GetCurrentContext(), v8::Null(v8::Isolate::GetCurrent())); return *this;};

    template <typename U>
    auto reject(U&& exception) -> promise<void>&
    {m_v8_promise->Reject(v8::Isolate::GetCurrent()->GetCurrentContext(), v8pp::to_v8(v8::Isolate::GetCurrent(), std::forward<U>(exception))); return *this;}

    template <callable F0, callable F1>
    auto react(F0&& fulfilled_steps, F1&& rejected_steps = []{}) -> promise<void>&;

    ext::boolean is_resolved = false;
    ext::boolean is_rejected = false;

private:
    v8::Local<v8::Promise::Resolver> m_v8_promise;
};


template <typename ...Ts>
template <callable F0, callable F1>
auto promise<Ts...>::react(
        F0&& fulfilled_steps,
        F1&& rejected_steps)
        -> promise<Ts...>&
{
    JS_REALM_GET_RELEVANT(this);

    auto on_fulfilled_steps =
            [this_relevant_agent, fulfilled_steps = std::forward<F0>(fulfilled_steps)]<typename U>(U&& value) mutable
            {
                auto v8_value = v8pp::to_v8(this_relevant_agent, std::forward<U>(value));
                return_if (!v8_value.IsEmpty()) fulfilled_steps();
            };

    auto on_rejected_steps =
            [this_relevant_agent, rejected_steps = std::forward<F1>(rejected_steps)]<typename U>(U&& reason) mutable
            {
                auto v8_reason = v8pp::to_v8(this_relevant_agent, std::forward<U>(reason));
                return_if (!v8_reason.IsEmpty()) rejected_steps();
            };

    decltype(auto) on_fulfilled = v8::Function::New(this_relevant_agent, std::move(on_fulfilled_steps));
    decltype(auto) on_rejected  = v8::Function::New(this_relevant_agent, std::move(on_rejected_steps));

    // TODO
    // decltype(auto) constructor = m_v8_promise->GetPromise()->GetCreationContextChecked()->Get
}


_EXT_END


#endif //SBROWSER2_SRC_EXT_PROMISE_HPP
