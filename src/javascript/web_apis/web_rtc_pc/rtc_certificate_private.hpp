#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_CERTIFICATE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_CERTIFICATE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS(web_rtc::pc, rtc_certificate) : virtual dom_object_private
{
    ext::string keying_material_handle;

};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_CERTIFICATE_PRIVATE_HPP
