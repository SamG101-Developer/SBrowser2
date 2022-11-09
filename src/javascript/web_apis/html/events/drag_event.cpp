#include "drag_event.hpp"
#include "drag_event_private.hpp"

#include "html/dnd/data_transfer.hpp"


html::events::drag_event::drag_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL(drag_event);

    ACCESS_PIMPL(drag_event);
    d->data_transfer = std::unique_ptr<dnd::data_transfer>{event_init[u"dataTransfer"].to<dnd::data_transfer*>()};
}


auto html::events::drag_event::get_data_transfer() const -> dnd::data_transfer*
{
    ACCESS_PIMPL(const drag_event);
    return d->data_transfer.get();
}
