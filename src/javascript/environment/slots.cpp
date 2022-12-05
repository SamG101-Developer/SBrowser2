module;
#include <v8pp/convert.hpp>


module js.env.slots;
import js.env.realms;

template <typename T>
auto js::env::get_slot(const env& e, const slot<T>& slot) -> T&
{
    return v8pp::from_v8<T>(e.js.agent(), e.js.global()->GetInternalField(slot));
}


template <typename T>
auto js::env::set_slot(const env& e, const slot<T>& slot, T&& value) -> void
{
    e.js.global()->SetInternalField(slot, v8pp::to_v8(e.js.agent(), std::forward<T>(value)));
}


template <typename T>
auto js::env::del_slot(const env& e, const slot<T>& slot) -> void
{
    e.js.global()->GetInternalField(slot).Clear();
}
