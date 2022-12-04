#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_REPORTING_OBSERVER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_REPORTING_OBSERVER_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(reporting)

namespace reporting {class report;}


DEFINE_PRIVATE_CLASS(reporting, reporting_observer) : virtual dom_object_private
{
    detail::reporting_observer_callback_t callback;
    detail::reporting_observer_options_t options;
    ext::queue<report*> report_queue;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_REPORTING_OBSERVER_PRIVATE_HPP
