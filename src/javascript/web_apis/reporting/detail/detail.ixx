module;
#include "ext/macros/pimpl.hpp"
#include <v8-forward.h>
#include <tl/optional.hpp>


export module apis.reporting.detail;

import apis.html.concepts;

import apis.dom.types;
import apis.fetch.types;
import apis.html.types;
import apis.reporting.types;
import apis.url.types;

import ext.core;
import js.env.realms;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(reporting)
{
    // Non "abstract operation" detail method
    template <html::concepts::is_serializable T>
    /* [2.3  ] */ auto generate_report(T* data, ext::string&& type, ext::string&& destination, const js::env::env& object = js::env::env::current(), ext::optional<url::detail::url_t&> url = ext::nulloptr) -> std::unique_ptr<report_t>;
    /* [2.4  ] */ auto serialize_list_or_reports_to_json(ext::span<report_t*> reports) -> ext::string;
    /* [3.1  ] */ auto initialize_global_endpoints_list(html::window_or_worker_global_scope* context, const fetch::detail::response_t& response) -> void;
    /* [3.3  ] */ auto process_reporting_endpoints_for_response(const fetch::detail::response_t& response) -> ext::vector<endpoint_t*>;
    /* [3.4  ] */ auto generate_report(dom::node* object, ext::string&& type, ext::string&& destination, const js::env::env& environment) -> void;
    /* [3.5.1] */ auto send_report(ext::span<report_t*>, html::window_or_worker_global_scope* context) -> void;
    /* [3.5.2] */ auto attempt_deliver_reports_to_endpoint(const endpoint_t& endpoint, const html::detail::origin_t& origin, ext::span<report_t*> reports) -> delivery_response_t;

//    auto notify_reporting_observers_on_scope_with_report(
//            html::workers::worker_global_scope* scope)
//            -> void;

//    auto add_report_to_observer(
//            const report_t& report,
//            reporting_observer* observer)
//            -> void;

//    auto invoke_reporting_observers(
//            ext::vector_span<reporting_observer*> notify_list)
//            -> void;
};
