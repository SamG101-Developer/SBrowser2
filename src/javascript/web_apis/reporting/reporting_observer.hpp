#pragma once
#ifndef SBROWSER2_REPORTING_OBSERVER_HPP
#define SBROWSER2_REPORTING_OBSERVER_HPP

#include "dom_object.hpp"
namespace reporting {class reporting_observer;}

#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/queue.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(reporting)
namespace reporting {class report;}


class reporting::reporting_observer
        : public dom_object
{
public constructors:
    reporting_observer(detail::reporting_observer_callback_t&& callback, detail::reporting_observer_options_t&& options = {});

public js_methods:
    auto observe() -> void;
    auto disconnect() -> void;
    auto take_record() -> ext::vector<report*>;

private cpp_properties:
    detail::reporting_observer_callback_t m_callback;
    detail::reporting_observer_options_t m_options;
    ext::queue<detail::report_t*> m_report_queue;
};


#endif //SBROWSER2_REPORTING_OBSERVER_HPP
