module;
#include <memory>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/algorithm/contains.hpp>


module apis.performance_timeline.detail;
import apis.performance_timeline.types;
import apis.performance_timeline.performance_entry;
import apis.performance_timeline.performance_entry_private;
import apis.performance_timeline.performance_observer;
import apis.performance_timeline.performance_observer_private;

import apis.timing_entry.detail;

import ext.functional;
import ext.ranges;
import ext.set;
import ext.string;
import ext.vector;

import js.env.realms;
import js.env.slots;


auto performance_timeline::detail::queue_performance_entry(
        std::shared_ptr<performance_entry> new_entry)
        -> void
{
    // [1-3] Create the 'interested_observers' (set of PerformanceObservers), and get the 'entry_type' and the
    // 'relevant_environment' of the 'new_entry' PerformanceEntry object.
    auto interested_observers = ext::set<performance_observer*>{};
    auto entry_type = new_entry->d_func()->type;
    auto relevant_environment = js::env::env::relevant(new_entry.get());

    // [4] For each interested observer in the global object's [[ListOfRegisteredPerfomanceObservers]] whose 'options'
    // "type" matches 'type' or "entryTypes" contains 'type' (and that pass the 'should_add_entry(...)' check), add it
    // to the interested_observers.
    interested_observers = *js::env::get_slot(relevant_environment, js::env::slots::LIST_OF_REGISTERED_PERFORMANCE_OBSERVERS)
            | ranges::views::transform(&std::unique_ptr<detail::registered_performance_observer_t>::operator*)
            | ranges::views::filter([](auto&& registered) {return registered.options[u"type"].to<ext::string>() == entry_type || ranges::contains(registered.options[u"entryTypes"].to<ext::vector<ext::string>>(), std::move(entry_type));})
            | ranges::views::filter(&timing_entry::detail::should_add_entry)
            | ranges::to_set;

    // [5] Add the 'new_entry' to each PerformanceObserver's 'observer_buffer' stored in the private class.
    interested_observers | ranges::views::for_each([new_entry](auto* observer) {observer->d_func()->observer_buffer.emplace_back(new_entry);});

    // [6-8] Get the 'tuple' -- the value corresponding to the "entryType" value in the global object's
    // [[PerfomanceEntryBufferMap]]. Determine if the performance entry buffer 'is_full', and if the 'new_entry' should
    // be added.
    decltype(auto) tuple = *js::env::get_slot(relevant_environment, js::env::slots::PERFORMANCE_ENTRY_BUFFER_MAP)[u"entryType"];
    auto is_full = determine_if_performance_entry_buffer_is_full(tuple);
    auto should_add = timing_entry::detail::should_add_entry(new_entry.get());

    // [9] Emplace the 'new_entry' into the 'tuple's 'performance_entry_buffer' if the buffer isn't full and if 'new_entry'
    // should be added.buffer isn;
    if (!is_full && should_add)
        tuple.performance_entry_buffer.emplace_back(new_entry);

    // [10] Queue an performance observer task for the relevant global object.
    queue_perfomance_observer_task(relevant_environment.js.global());
}

