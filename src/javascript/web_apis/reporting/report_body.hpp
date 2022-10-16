#pragma once
#ifndef SBROWSER2_REPORT_BODY_HPP
#define SBROWSER2_REPORT_BODY_HPP

#include "dom_object.hpp"
namespace reporting {class report_body;}
namespace reporting {class report_body_private;}


class reporting::report_body
        : public virtual dom_object
{
public constructors:
    report_body();
    MAKE_PIMPL(report_body);
    MAKE_V8_AVAILABLE;
    MAKE_STRINGIFIER;
};


#endif //SBROWSER2_REPORT_BODY_HPP
