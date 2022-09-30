#include "payment_instruments.hpp"

#include <range/v3/action/remove.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/to_container.hpp>


auto payment::handler::payment_instruments::delete_(
        ext::string_view instrument_key)
        -> ext::promise<ext::boolean>
{
    ACCESS_PIMPL(payment_instruments);

    auto promise = ext::promise<ext::boolean>{};
    GO [&promise, &instrument_key, d] {promise.resolve(ranges::remove(d->map, instrument_key));};
    return promise;
}


auto payment::handler::payment_instruments::get(
        ext::string_view instrument_key)
        const -> ext::promise<ext::any>
{
    ACCESS_PIMPL(const payment_instruments);

    auto promise = ext::promise<ext::any>{};
    GO [&promise, &instrument_key, d] {d->map.contains(instrument_key) && promise.resolve(d->map.at(instrument_key));};
    return promise;
}


auto payment::handler::payment_instruments::keys()
        const -> ext::promise<ext::vector<ext::string>>
{
    ACCESS_PIMPL(const payment_instruments);

    auto promise = ext::promise<ext::vector<ext::string>>{};
    GO [&promise, d] {promise.resolve(d->map | ranges::views::keys | ranges::to<ext::vector<ext::string>>);};
    return promise;
}


auto payment::handler::payment_instruments::has(
        ext::string_view instrument_key)
        const -> ext::promise<ext::boolean>
{
    ACCESS_PIMPL(const payment_instruments);

    auto promise = ext::promise<ext::boolean>{};
    GO [&promise, &instrument_key, d] {promise.resolve(d->map.contains(instrument_key));};
    return promise;
}


auto payment::handler::payment_instruments::clear()
        -> ext::promise<void>
{
    ACCESS_PIMPL(const payment_instruments);

    auto promise = ext::promise<void>{};
    GO [&promise, d] {d->map.clear(); promise.resolve();};
    return promise;
}
