module;
#include "ext/macros.hpp"


export module apis.reporting.reporting_observer:p;

IMPORT_ALL_TYPES(reporting);


DEFINE_PRIVATE_CLASS(reporting, reporting_observer)
        : virtual dom_object_private
{
    reporting_observer_callback_t callback;
    reporting_observer_options_t options;
    ext::queue<report*> report_queue;
};
