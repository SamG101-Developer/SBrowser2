#include "payment_manager.hpp"
#include "payment_manager_private.hpp"


payment::handler::payment_manager::payment_manager()
{
    INIT_PIMPL(payment_manager);
}


auto payment::handler::payment_manager::get_instruments() const -> payment_instruments*
{
    ACCESS_PIMPL(const payment_manager);
    return d->instruments.get();
}


auto payment::handler::payment_manager::get_user_hint() const -> ext::string
{
    ACCESS_PIMPL(const payment_manager);
    return d->user_hint;
}


auto payment::handler::payment_manager::set_user_hint(
        ext::string new_user_hint)
        -> ext::string
{
    ACCESS_PIMPL(payment_manager);
    d->user_hint = new_user_hint;
}


auto payment::handler::payment_manager::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<payment_manager>{isolate}
        .inherit<dom_object>()
        .property("instruments", &payment_manager::get_instruments)
        .property("userHints", &payment_manager::get_user_hint)
        .auto_wrap_objects();

    return std::move(conversion);
}
