#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_DETAIL_LOCK_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_DETAIL_LOCK_INTERNALS_HPP

#include "ext/memory.ixx"
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

    auto request_lock(
            ext::promise<ext::any>& promise,
            v8::Isolate* agent,
            ext::string&& client_id,
            const lock_manager_t& manager,
            lock_granted_callback_t&& callback,
            resource_name_t&& name,
            lock_mode_t mode,
            ext::boolean if_availablle,
            ext::boolean steal,
            dom::abort::abort_signal* signal)
            -> std::unique_ptr<lock_request_t>;

    auto release_lock(
            lock_t& lock)
            -> void;

    auto process_lock_request_queue(
            lock_request_queue_t& queue)
            -> void;
}


struct web_locks::detail::lock_manager_t
{
    lock_request_queue_map_t lock_request_queue_map;
    ext::set<std::unique_ptr<lock_t>> held_lock_set;
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
};


struct web_locks::detail::lock_request_t
{
    v8::Isolate* agent;
    ext::string client_id;
    std::observer_ptr<lock_manager_t> manager;
    resource_name_t name;
    lock_mode_t mode;

    lock_granted_callback_t callback;
    ext::promise<ext::any> promise;
    std::observer_ptr<dom::abort::abort_signal> signal;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_DETAIL_LOCK_INTERNALS_HPP
