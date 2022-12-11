export module js.env.slots;
import ext.boolean;
import ext.number;
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
