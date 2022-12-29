module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/other.hpp"
#include "javascript/macros/expose.hpp"


export module apis.reporting.report_body;
import apis.dom_object;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(reporting, report_body)
        : public virtual dom_object
{
public constructors:
    report_body();
    MAKE_PIMPL(report_body);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);
    MAKE_STRINGIFIER;
};
