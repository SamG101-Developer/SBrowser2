#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_REPORT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_REPORT_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(reporting)
#include INCLUDE_INNER_TYPES(url)
namespace reporting {class report_body;}


DEFINE_PRIVATE_CLASS(reporting, report) : virtual dom_object_private
{
    std::unique_ptr<detail::report_t> report;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_REPORT_PRIVATE_HPP
