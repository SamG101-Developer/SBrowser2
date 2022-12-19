module;
#include <memory>


export module js.env.slots;

import apis.performance_timeline.types;

import ext.boolean;
import ext.map;
import ext.number;
import ext.string;
import ext.vector;

namespace dom {class range;}


namespace js
{
    template <typename T>
    struct slot
    {
        static ext::number<int> counter;
        ext::number<int> id;
        using value_t = T;

        slot() {id = (counter += 1);}
    };
}


namespace js::env
{
    class settings_t;

    export namespace slots
    {
        /* [HTML] */
        const auto MUTATION_OBSERVERS = slot{};
        const auto MUTATION_OBSERVERS_MICROTASK_QUEUED = slot<ext::boolean>{};
        const auto NOTIFY_OBSERVERS = slot{};
        const auto SIGNAL_SLOTS = slot{};
        const auto SETTINGS = slot<settings_t*>{};
        const auto LIVE_RANGES = slot<ext::vector<dom::range*>*>{};
        const auto CE_REACTIONS = slot{};

        /* [PERFORMANCE-TIMELINE] */
        const auto PERFORMANCE_OBSERVER_TASK_QUEUED_FLAG = slot<ext::boolean>{};
        const auto LIST_OF_REGISTERED_PERFORMANCE_OBSERVERS = slot<ext::vector<std::unique_ptr<performance_timeline::detail::registered_performance_observer_t>>*>{};
        const auto PERFORMANCE_ENTRY_BUFFER_MAP = slot<ext::map<ext::string, std::unique_ptr<performance_timeline::detail::performance_entry_buffer_map_tuple_t>>*>{};
        const auto FROZEN_ARRAY_SUPPORTED_ENTRY_TYPES = slot<ext::vector<ext::string>>{};

        /* [MEDIACAPTURE-MAIN] */
        // constexpr auto

        /* [FETCH] */
        // constexpr auto connection_pool = 7;
    }
}


namespace js::env
{
    class env;
    export template <typename T> auto get_slot(const env& e, const slot<T>& slot) -> T&;
    export template <typename T> auto set_slot(const env& e, const slot<T>& slot, T&& value) -> void;
    export template <typename T> auto del_slot(const env& e, const slot<T>& slot) -> void;
}
