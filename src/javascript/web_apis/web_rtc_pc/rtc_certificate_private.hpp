#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_CERTIFICATE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_CERTIFICATE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(web_rtc_pc)


DEFINE_PRIVATE_CLASS(web_rtc::pc, rtc_certificate) : virtual dom_object_private
{
    detail::keying_material_t keying_material_handle;
    std::unique_ptr<detail::certificate_t> certificate;
    html::detail::origin_t origin;

    hr_time::epoch_time_stamp expires;

    detail::rtc_configuration_t configuration;
    ext::boolean is_closed = false;
    ext::boolean negotiation_needed = false;
    ext::vector<detail::operation_t> operations = {};
    ext::boolean update_negotiation_needed_flag_on_empty_chain = false;
    ext::string last_created_offer = u8"";
    ext::string last_created_answer = u8"";
    ext::vector<int> early_candidates = {}; // TODO -> not <int>

    ext::string pending_local_description = {};
    ext::string current_local_description = {};
    ext::string pending_remote_description = {};
    ext::string current_remote_description = {};
    ext::set<int> locallce_credentials_to_replace = {}; // TODO -> not <int>
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_RTC_PC_RTC_CERTIFICATE_PRIVATE_HPP
