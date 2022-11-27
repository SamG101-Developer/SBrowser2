#include "media_session.hpp"
#include "media_session_private.hpp"

#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "html/navigators/navigator.hpp"
#include "html/navigators/navigator_private.hpp"

#include "mediasession/detail/media_session_internals.hpp"
#include "mediasession/media_metadata.hpp"
#include "mediasession/media_metadata_private.hpp"


auto mediasession::media_session::get_metadata() const -> media_metadata*
{
    ACCESS_PIMPL(const media_session);
    return d->metadata.get();
}


auto mediasession::media_session::set_metadata(mediasession::media_metadata* new_metadata) -> media_metadata*
{
    ACCESS_PIMPL(media_session);
    if (d->metadata) d->metadata->d_func()->media_session = nullptr;
    d->metadata.reset(new_metadata);
    if (d->metadata) d->metadata->d_func()->media_session = this;
    GO &detail::update_metadata;
}
