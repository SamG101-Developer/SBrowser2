#pragma once
#ifndef SBROWSER2_REPORT_HPP
#define SBROWSER2_REPORT_HPP

#include "dom_object.hpp"
namespace reporting {class report;}
namespace reporting {class report_private;}

namespace reporting {class report_body;}


class reporting::report
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(report);
    MAKE_PIMPL(report);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;

private js_properties:
    DEFINE_GETTER(type, ext::string_view);
    DEFINE_GETTER(url, ext::string);
    DEFINE_GETTER(body, report_body*);
};


#endif //SBROWSER2_REPORT_HPP
