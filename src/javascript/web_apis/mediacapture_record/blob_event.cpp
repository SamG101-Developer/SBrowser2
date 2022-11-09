#include "blob_event.hpp"
#include "blob_event_private.hpp"


auto mediacapture::record::blob_event::get_blob() const -> file_api::blob*
{
    ACCESS_PIMPL(const blob_event);
    return d->data.get();
}
