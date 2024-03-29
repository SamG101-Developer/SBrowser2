#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_CERTIFICATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_CERTIFICATE_HPP

// Inheritance Includes & This Class

namespace web_rtc::pc {class rtc_certificate;}
namespace web_rtc::pc {class rtc_certificate_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(web_rtc_pc)


class web_rtc::pc::rtc_certificate
        : public dom_object
{
public constructors:
    rtc_certificate();
    MAKE_PIMPL(rtc_certificate);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto get_fingerprints() -> ext::vector<detail::rtc_dtls_fingerprint_t>;

private js_properties:
    DEFINE_GETTER(expires, hr_time::epoch_time_stamp);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_CERTIFICATE_HPP
