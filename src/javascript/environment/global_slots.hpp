#ifndef SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_GLOBAL_SLOTS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_GLOBAL_SLOTS_HPP

namespace js::global_slots // TODO -> to enum??
{
    /* [HTML] */
    constexpr auto mutation_observers = 0;
    constexpr auto mutation_observer_microtask_queued = 1;
    constexpr auto notify_observers = 2;
    constexpr auto signal_slots = 3;
    constexpr auto settings = 4;
    constexpr auto live_ranges = 5;
    constexpr auto ce_reactions = 6;

    /* [MEDIACAPTURE-MAIN] */
    // constexpr auto

    /* [FETCH] */
    constexpr auto connection_pool = 7;
}


namespace js::env
{
    class env;
    template <typename T> auto get_slot(const env& e, int slot) -> T;
    template <typename T> auto set_slot(const env& e, int slot, T&& value) -> void;
    auto del_slot(const env& e, int slot) -> void; // TODO : return deleted?
}


#endif //SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_GLOBAL_SLOTS_HPP
