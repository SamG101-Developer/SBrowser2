#include "remote_playback.hpp"
#include "remote_playback_private.hpp"




#include <range/v3/action/remove.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/map.hpp>


auto remote_playback::remote_playback::watch_availability(
        detail::remote_playback_availability_callback&& callback)
        -> ext::promise<ext::number<long>>
{
    auto promise = ext::promise<ext::number<long>>{};

    GO [&promise]
    {
        // TODO : HTMLMediaElement->disableRemotePlayback attribute (which HTMLMediaElement <= back_ptr from d?)
        // TODO
    };

    return promise;
}


auto remote_playback::remote_playback::cancel_watch_availability(
        ext::optional<ext::number<long>> id)
        -> ext::promise<void>
{
    ACCESS_PIMPL(remote_playback);
    using enum dom::detail::dom_exception_error_t;
    auto promise = ext::promise<void>{};

    GO [d, &promise, id = std::move(id)]
    {
        // TODO : HTMLMediaElement->disableRemotePlayback attribute (which HTMLMediaElement <= back_ptr from d?)

        if (!id.has_value())
            d->availability_callbacks.clear();
        else if (ranges::contains(d->availability_callbacks | ranges::views::keys, *id))
            d->availability_callbacks |= ranges::actions::remove(*id);
        else
            return promise.reject(dom::other::dom_exception{u8"Remote playback device doesn't exist", NOT_FOUND_ERR});

        if (d->availability_callbacks.empty())
            ; // TODO

        promise.resolve();
    };

    return promise;
}
