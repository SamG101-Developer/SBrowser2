module;
#include "ext/macros/pimpl.hpp"


export module apis.reporting.reporting_observer_private;
import apis.dom_object_private;

import apis.reporting.types;


DEFINE_PRIVATE_CLASS(reporting, reporting_observer)
        : virtual dom_object_private
{
    reporting_observer_callback_t callback;
    reporting_observer_options_t options;
    ext::queue<report*> report_queue;
};
