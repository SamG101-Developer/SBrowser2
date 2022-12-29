module;
#include "ext/macros/pimpl.hpp"
#include <v8-forward.h>
#include <tl/optional.hpp>
#include <tuplet/tuple.hpp>


export module apis.web_idl.detail;
import ext.core;
import ext.js;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(web_idl)
{
    /* 3.2.4.9 */
    template <ext::arithmetic T>
    auto integer_part(T&& value) -> long long;

    template <int BitLength, bool Signed>
    auto convert_to_int(v8::Local<v8::Number>) -> ext::number<std::conditional_t<Signed, int64_t, uint64_t>>;

    /* 3.2.23.1 */
    template <typename T>
    auto create_promise(v8::Local<v8::Context> realm) -> ext::promise<T>;

    template <typename T>
    auto create_resolved_promise(T&& x, v8::Local<v8::Context> realm) -> ext::promise<T>;

    auto create_resolved_promise(v8::Local<v8::Context> realm) -> ext::promise<void>;

    template <typename T>
    auto create_rejected_promise(ext::any&& reason, v8::Local<v8::Context> realm) -> ext::promise<T>;

    template <typename T>
    auto resolve_promise(ext::promise<T>& promise, v8::Local<v8::Context> realm, T&& x) -> ext::promise<T>&;

    auto resolve_promise(ext::promise<void>& promise, v8::Local<v8::Context> realm) -> ext::promise<void>&;

    template <typename T, typename U>
    auto reject_promise(ext::promise<T>& promise, v8::Local<v8::Context> realm, U&& reason) -> ext::promise<T>&;

    template <typename T, ext::callable F0, ext::callable F1>
    auto react(ext::promise<T>& promise, v8::Local<v8::Context> realm, ext::optional<F0>&& fullfilled_steps = ext::nullopt, ext::optional<F1>&& rejected_steps = ext::nullopt) -> void;

    template <typename T, ext::callable F>
    auto upon_fulfillment(ext::promise<T>& promise, v8::Local<v8::Context> realm, F&& steps) -> ext::promise<T>&;

    template <typename T, ext::callable F>
    auto upon_rejection(ext::promise<T>& promise, v8::Local<v8::Context> realm, F&& steps) -> ext::promise<T>&;

    template <typename T, ext::callable F>
    auto upon_settlement(ext::promise<T>& promise, v8::Local<v8::Context> realm, F&& steps) -> ext::promise<T>&;

    template <typename T, ext::callable F0, ext::callable F1>
    auto wait_for_all(ext::span<ext::promise<T>*> promises, v8::Local<v8::Context> realm, F0&& success_steps, F1&& failure_steps) -> void;

    template <typename T>
    auto get_promise_for_waiting_for_all(ext::span<ext::promise<T>*> promises, v8::Local<v8::Context> realm) -> ext::promise<T>;

    template <typename T>
    auto mark_as_handled(ext::promise<T>& promise) -> void;

    // Not in spec
    template <typename T>
    auto wait_for_promise_to_fulfill_or_reject(ext::promise<T>&, v8::Local<v8::Context> realm) -> void;

    template <typename T>
    auto has_fulfilled(ext::promise<T>& promise, v8::Local<v8::Context> realm) -> ext::tuple<ext::boolean, ext::optional<T>>;

    template <typename E, typename T>
    auto has_rejected(ext::promise<T>& promise, v8::Local<v8::Context> realm) -> ext::tuple<ext::boolean, ext::optional<E>>;

    /* 3.2.25 */
    template <typename T>
    auto create_array_buffer(T&& byte_sequence, v8::Local<v8::Context> realm) -> ext::array_buffer;

    template <typename U, typename T>
    auto create_array_buffer_view(T&& byte_sequence, v8::Local<v8::Context> realm) -> U;

    auto get_copy_of_bytes_in_buffer_source(ext::buffer_source& source, v8::Local<v8::Context> realm) -> void*;

    auto byte_length(ext::buffer_source& source, v8::Local<v8::Context> realm) -> ext::number<size_t>;

    auto underlying_data(ext::buffer_source& source, v8::Local<v8::Context> realm) -> ext::array_buffer;

    template <typename T>
    auto write(T&& byte_sequence, ext::array_buffer& array_buffer, v8::Local<v8::Context> realm) -> ext::array_buffer&;

    template <typename T>
    auto write(T&& byte_sequence, ext::array_buffer_view& array_buffer, v8::Local<v8::Context> realm) -> ext::array_buffer_view&;

    auto detach_array_buffer(ext::array_buffer& array_buffer, v8::Local<v8::Context> realm) -> void;

    auto is_detached(ext::array_buffer& array_buffer, v8::Local<v8::Context> realm) -> ext::boolean;

    auto transfer(ext::array_buffer& array_buffer, v8::Local<v8::Context> realm, v8::Local<v8::Context> target_realm);

    // TDODO : not in spec
    auto viewed_buffer(ext::array_buffer_view& array_buffer_view) -> ext::array_buffer&;
}
