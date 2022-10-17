#include "track_event.hpp"
#include "track_event_private.hpp"

#include "html/basic_media/abstract_track.hpp"


html::events::track_event::track_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::nodes::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL(track_event);

    ACCESS_PIMPL(track_event);
    d->track = std::unique_ptr<basic_media::abstract_track>(event_init[u8"track"].to<basic_media::abstract_track*>());
}


auto html::events::track_event::get_track() const -> basic_media::abstract_track*
{
    ACCESS_PIMPL(const track_event);
    return d->track.get();
}
