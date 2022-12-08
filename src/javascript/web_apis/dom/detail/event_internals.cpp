#include "event_internals.hpp"

#include "ext/assertion.hpp"


#include "ext/hashing.ixx"
#include "ext/keywords.ixx"










#include "event_timing/detail/timing_internals.hpp"
#include "event_timing/performance_event_timing.hpp"

#include "hr_time/detail/time_internals.hpp"
#include "indexed_db/events/idb_version_change_event.hpp"
#include "pointer_events/pointer_event.hpp"
#include "touch_events/touch_event.hpp"
#include "ui_events/mouse_event.hpp

#include <fmt/format.h>
#include <range/v3/to_container.hpp>
#include <range/v3/action/remove.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/view/empty.hpp>
#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/slice.hpp>


auto dom::detail::flatten_more(
        event_listener_options_t&& options)
        -> ext::map<ext::string, ext::any>
{
    // Return {capture: true} if the options is a bool value, otherwise the map already being held in the variant
    // object. This just acts as a normalizer to get the "capture" value in map form.
    return ext::holds_alternative<ext::boolean>(options)
           ? ext::map<ext::string, ext::any>{{u"capture", ext::get<ext::boolean>(options)}}
           : ext::get<ext::map<ext::string, ext::any>>(options);
}


auto dom::detail::flatten(
        event_listener_options_t&& options)
        -> ext::boolean
{
    // Return the boolean "capture" value if a boolean value is being stored in the variant, otherwise the capture
    // option of the map. This just acts as a normalizer to get the boolean representation of the "capture" value
    return ext::holds_alternative<ext::boolean>(options)
           ? ext::get<ext::boolean>(options)
           : ext::get<ext::map<ext::string, ext::any>>(options).at(u"capture").to<ext::boolean>();
}
