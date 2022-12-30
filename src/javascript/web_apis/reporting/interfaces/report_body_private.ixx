module;
#include "ext/macros.hpp"


export module apis.reporting.report_body:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(reporting, report_body)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(report_body);
};
