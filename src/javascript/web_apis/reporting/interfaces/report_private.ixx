module;
#include "ext/macros.hpp"


export module apis.reporting.report:p;
import apis.dom_object;

IMPORT_ALL_TYPES(reporting);


DEFINE_PRIVATE_CLASS(reporting, report)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(report);

public:
    std::unique_ptr<detail::report_t> report;
};
