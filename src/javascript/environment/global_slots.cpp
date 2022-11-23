#include "global_slots.hpp"

#include "javascript/environment/realms.hpp"


template <typename T>
inline auto js::env::get_slot(const js::env::env& e, int slot) -> T
{
    return v8pp::from_v8<T>(e.js.agent(), e.js.global()->GetInternalField(slot));
}


template <typename T>
inline auto js::env::set_slot(const js::env::env& e, int slot, T&& value) -> void
{
    e.js.global()->SetInternalField(slot, v8pp::to_v8(e.js.agent(), std::forward<T>(value)));
}


inline auto js::env::del_slot(const js::env::env& e, int slot) -> void
{
    e.js.global()->GetInternalField(slot).Clear();
}
