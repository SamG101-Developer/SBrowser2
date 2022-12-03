#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_DETAIL_REPORTING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_DETAIL_REPORTING_INTERNALS_HPP


#include "ext/map.ixx"
#include "ext/number.ixx"
#include "ext/optional.hpp"
#include "ext/span.hpp"
#include "ext/string.hpp"
#include <v8-forward.h>

#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(url)
#include INCLUDE_INNER_TYPES(reporting)
#include INCLUDE_CONCEPTS(html)

namespace dom::nodes {class document;}
namespace html::workers {class worker_global_scope;}
namespace reporting {class report_body;}
namespace reporting {class reporting_observer;}


namespace reporting::detail
{
    template <html::concepts::is_serializable T>
    auto generate_report(
           T* serializable_object,
           ext::string&& type,
           ext::string&& destination,
           ext::optional<v8::Local<v8::Object>> object = ext::nullopt,
           ext::optional<url::detail::url_t*> url = ext::nullopt)
           -> std::unique_ptr<report_t>;
//
//    auto serialize_list_or_reports_to_json(
//            ext::vector_span<report_t*>)
//            -> ext::string;
//
//    auto process_reporting_endpoints_for_response(
//            const fetch::detail::response_t& response)
//            -> ext::vector<endpoint_t*>;

    template <html::concepts::is_serializable T>
    auto generate_report(
            T serializable,
            ext::string&& type,
            ext::string&& destination,
            v8::Local<v8::Object> settings)
            -> void;

//    auto initialize_global_endpoints_list(
//            html::workers::worker_global_scope* scope,
//            const fetch::detail::response_t& response)
//            -> void;
//
//    auto send_report(
//            ext::vector_span<report_t*>,
//            html::workers::worker_global_scope* context)
//            -> void;
//
//    auto deliver_reports_to_endpoint(
//            const endpoint_t& endpoint,
//            const html::detail::origin_t& origin,
//            ext::vector_span<report_t*> reports)
//            -> delivery_response_t;
//
//    auto notify_reporting_observers_on_scope_with_report(
//            html::workers::worker_global_scope* scope)
//            -> void;
//
//    auto add_report_to_observer(
//            const report_t& report,
//            reporting_observer* observer)
//            -> void;
//
//    auto invoke_reporting_observers(
//            ext::vector_span<reporting_observer*> notify_list)
//            -> void;
};


struct reporting::detail::endpoint_t
{
    ext::string name;
    std::unique_ptr<url::detail::url_t> url;
    ext::number<uint> failures;
};


struct reporting::detail::report_t
{
    std::unique_ptr<report_body> body;
    std::unique_ptr<url::detail::url_t> url;
    ext::string user_agent;
    ext::string destination;
    detail::report_type_t type;
    hr_time::epoch_time_stamp timestamp;
    ext::number<uint> attempts;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_DETAIL_REPORTING_INTERNALS_HPP
