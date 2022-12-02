#pragma once
#ifndef SBROWSER2_REPORTING_OBSERVER_HPP
#define SBROWSER2_REPORTING_OBSERVER_HPP

#include "dom_object.hpp"
namespace reporting {class reporting_observer;}
namespace reporting {class reporting_observer_private;}

#include "ext/functional.ixx"
#include "ext/map.ixx"
#include "ext/queue.ixx"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(reporting)
namespace reporting {class report;}


class reporting::reporting_observer
        : public virtual dom_object
{
public constructors:
    reporting_observer(detail::reporting_observer_callback_t&& callback, detail::reporting_observer_options_t&& options = {});
    MAKE_PIMPL(reporting_observer);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;

public js_methods:
    auto observe() -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<report*>;
};


#endif //SBROWSER2_REPORTING_OBSERVER_HPP
