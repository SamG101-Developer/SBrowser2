#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_DETAIL_LOCK_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_DETAIL_LOCK_INTERNALS_HPP

#include "ext/memory.hpp"
#include "ext/promise.hpp"
#include "ext/set.hpp"
#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(web_locks)
namespace js::env {class env;}
namespace dom::abort {class abort_signal;}


namespace web_locks::detail
{
    auto obtain_lock_manager(
            js::env::env& e)
            -> void;

    auto grantable(
            const lock_request_t&)
            -> ext::boolean;

    auto terminate_remaining_locks_and_Requests(
            v8::Isolate* agent)
            -> void;
}


struct web_locks::detail::lock_manager_t
{
    lock_request_queue_map_t lock_request_queue_map;
};


struct web_locks::detail::lock_t
{
    lock_t();

    v8::Isolate* agent;
    ext::string client_id;
    std::observer_ptr<lock_manager_t> manager;
    resource_name_t name;
    lock_mode_t mode;
    ext::promise<void> waiting_promise;
    ext::promise<decltype(waiting_promise)> released_promise;
    ext::set<std::unique_ptr<lock_t>> held_lock_set;
};


struct web_locks::detail::lock_request_t
{
    v8::Isolate* agent;
    ext::string client_id;
    std::observer_ptr<lock_manager_t> manager;
    resource_name_t name;
    lock_mode_t mode;

    ext::function<void()> callback;
    ext::promise<void> promise;
    std::observer_ptr<dom::abort::abort_signal> signal;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_DETAIL_LOCK_INTERNALS_HPP
