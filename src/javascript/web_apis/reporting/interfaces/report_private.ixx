module;
#include "ext/macros/pimpl.hpp"


export module apis.reporting.report_private;
import apis.dom_object_private;

import apis.reporting.types;


DEFINE_PRIVATE_CLASS(reporting, report)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(report);

public:
    std::unique_ptr<detail::report_t> report;
};
