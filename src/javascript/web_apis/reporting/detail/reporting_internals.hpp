#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_DETAIL_REPORTING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_DETAIL_REPORTING_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/number.hpp"
#include "ext/optional.hpp"
#include "ext/string.hpp"
#include <v8-forward.h>

#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(high_resolution_time)
#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(url)
#include USE_INNER_TYPES(reporting)

namespace dom::nodes {class document;}
namespace html::mixins {class serializable;}
namespace html::workers {class worker_global_scope;}
namespace reporting {class reporting_observer;}


namespace reporting::detail
{
    auto queue_report(
            html::mixins::serializable* serializable_object,
            ext::string&& type,
            ext::string&& destination,
            ext::optional<v8::Local<v8::Object>> object = ext::nullopt,
            ext::optional<url::detail::url_t> url = ext::nullopt)
            -> report_t;

    auto serialize_list_or_reports_to_json(
            ext::vector_view<report_t*>)
            -> ext::string;

    auto process_reporting_endpoints_for_response(
            const fetch::detail::response_t& response)
            -> ext::vector<endpoint_t*>;

    template <type_is<dom::nodes::document, html::workers::worker_global_scope> T>
    auto generate_report_of_type_with_data(
            T* context,
            ext::string&& type,
            ext::string&& destination,
            html::mixins::serializable* serializable_object)
            -> void;

    auto initialize_global_endpoints_list(
            html::workers::worker_global_scope* scope,
            const fetch::detail::response_t& response)
            -> void;

    auto send_report(
            ext::vector_view<report_t*>,
            html::workers::worker_global_scope* context)
            -> void;

    auto deliver_reports_to_endpoint(
            const endpoint_t& endpoint,
            const html::detail::origin_t& origin,
            ext::vector_view<report_t*> reports)
            -> delivery_response_t;

    auto notify_reporting_observers_on_scope_with_report(
            html::workers::worker_global_scope* scope)
            -> void;

    auto add_report_to_observer(
            const report_t& report,
            reporting_observer* observer)
            -> void;

    auto invoke_reporting_observers(
            ext::vector_view<reporting_observer*> notify_list)
            -> void;
};


struct reporting::detail::endpoint_t
{
    ext::string name;
    url::detail::url_t& url;
    ext::number<int> failures;
};


struct reporting::detail::report_t
{
    ext::map<ext::string, ext::any> body;
    ext::string url;
    ext::string user_agent;
    ext::string destination;
    report_type_t type;
    high_resolution_time::detail::epoch_time_stamp_t timestamp;
    ext::number<int> counter;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING_DETAIL_REPORTING_INTERNALS_HPP