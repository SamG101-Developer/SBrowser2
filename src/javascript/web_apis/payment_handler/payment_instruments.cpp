#include "payment_instruments.hpp"


auto payment::handler::payment_instruments::delete_(
        ext::string_view instrument_key)
        -> ext::promise<ext::boolean>
{
    ACCESS_PIMPL(payment_instruments);

    auto promise = ext::promise<ext::boolean>{};
    go [&promise, d] {promise.resolve(d->)};
}
