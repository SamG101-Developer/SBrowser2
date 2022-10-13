#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_REPORT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_REPORT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(reporting)
#include INCLUDE_INNER_TYPES(url)
namespace reporting {class report_body;}


DEFINE_PRIVATE_CLASS(reporting, report) : virtual dom_object_private
{
    std::unique_ptr<report_body> body;
    std::unique_ptr<url::detail::url_t> url;
    ext::string user_agent;
    ext::string destination;
    detail::report_type_t type;
    hr_time::epoch_time_stamp timestamp;
    ext::number<uint> attempts;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_REPORT_PRIVATE_HPP
