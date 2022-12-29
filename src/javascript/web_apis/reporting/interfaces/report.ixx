module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/other.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.reporting.report;
import apis.dom_object;

import apis.reporting.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(reporting, report)
        : public virtual dom_object
{
public constructors:
    MAKE_PIMPL(report);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);
    MAKE_STRINGIFIER;

private js_properties:
    DEFINE_GETTER(type, ext::string_view);
    DEFINE_GETTER(url, ext::string);
    DEFINE_GETTER(body, report_body*);
};
