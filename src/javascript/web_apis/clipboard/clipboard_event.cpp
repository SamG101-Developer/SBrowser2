#include "clipboard_event.hpp"

#include "html/dnd/data_transfer.hpp"


clipboard::clipboard_event::clipboard_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event(std::move(event_type), std::move(event_init))
        , SET_PROPERTY_FROM_OPTIONS(event_init, clipboard_data, nullptr)
{}
