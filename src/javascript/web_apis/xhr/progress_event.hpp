#ifndef SBROWSER2_PROGRESS_EVENT_HPP
#define SBROWSER2_PROGRESS_EVENT_HPP

#include "dom/events/event.hpp"
namespace xhr {class progress_event;}


class xhr::progress_event
        : public dom::events::event
{
public constructors:
    progress_event() = default;
    progress_event(ext::string_view event_type, ext::string_any_map_view event_init);

private js_properties:
    ext::property<ext::boolean> length_computable;
    ext::property<ext::number<ulonglong>> loaded;
    ext::property<ext::number<ulonglong>> total;
};

#endif //SBROWSER2_PROGRESS_EVENT_HPP
