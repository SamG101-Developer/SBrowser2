module;
#include "ext/macros/macros.hpp"


export module apis.reporting.report_body_private;
import apis.dom_object_private;


DEFINE_PRIVATE_CLASS(reporting, report_body)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(report_body);
};
