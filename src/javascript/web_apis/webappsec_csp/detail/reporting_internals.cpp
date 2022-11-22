#include "reporting_internals.hpp"

#include "ext/casting.hpp"
#include "ext/pair.hpp"
#include "ext/ranges.hpp"
#include "fetch/_typedefs.hpp"
#include "javascript/environment/realms.hpp"

#include "dom/detail/event_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/detail/shadow_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_private.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/element_private.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "fetch/detail/body_internals.hpp"
#include "fetch/detail/fetch_internals.hpp"
#include "fetch/detail/http_internals.hpp"
#include "fetch/detail/request_internals.hpp"

#include "webappsec_csp/csp_violation_report_body.hpp"
#include "webappsec_csp/csp_violation_report_body_private.hpp"
#include "webappsec_csp/security_policy_violation_event.hpp"
#include "webappsec_csp/security_policy_violation_event_private.hpp"
#include "webappsec_csp/detail/csp_internals.hpp"
#include "webappsec_csp/detail/violation_internals.hpp"

#include "html/detail/task_internals.hpp"
#include "infra/detail/infra_strings_internals.hpp"
#include "reporting/detail/reporting_internals.hpp"
#include "url/detail/url_internals.hpp"


auto webappsec::detail::strip_url_for_violation_report(
        url::detail::url_t& url)
        -> ext::string
{
    return_if (!fetch::detail::is_http_scheme(url.scheme)) url.scheme;
    url.fragment.clear();
    url.username.clear();
    url.password.clear();
    return url::detail::url_serializer(url);
}


auto webappsec::detail::report_violation(
        violation_t& violation)
        -> void
{
    decltype(auto) e = js::env::env::from_global_object(violation.global_object);
    decltype(auto) target = dom_cast<dom::nodes::node*>(violation.element.get()); // TODO : dom::nodes::event_target*?

    dom::detail::queue_task(html::detail::dom_manipulation_task_source, // TODO : task source
            [&violation, &target, &e]
            {
        auto window = e.cpp.global<dom::nodes::window*>();
        if (target && window && dom::detail::shadow_including_root(target) != window->d_func()->document.get())
            target = nullptr;

        if (!target)
            target = window->d_func()->document.get(); // TODO : other global object types

        dom::detail::fire_event<csp::security_policy_violation_event>(u"securitypolicyviolation", target,
                {
            {u"documentURI", strip_url_for_violation_report(violation.url())},
            {u"referrer", strip_url_for_violation_report(violation.url())},
            {u"blockedURI", obtain_blocked_uri_of_violations_resource(violation.resource)},
            {u"effectiveDirective", violation.effective_directive},
            {u"originalPolicy", serialize_csp(*violation.policy)},
            {u"disposition", violation.disposition},
            {u"sourceFile", strip_url_for_violation_report(*violation.source_file)},
            {u"statusCode", violation.status},
            {u"lineNumber", violation.line_number},
            {u"columnNumber", violation.column_number},
            {u"sample", violation.sample},
            {u"bubbles", true},
            {u"composed", true}
                });

        if (ranges::contains(violation.policy->directive_set | ranges::views::keys, u"report-uri") && !ranges::contains(violation.policy->directive_set | ranges::views::keys, u"report-to"))
        {
            auto directive = *ranges::find_if(violation.policy->directive_set, BIND_FRONT(ext::pair_key_matches, u"report-uri"));

            for (auto token: directive | ranges::views::split_string(u' ')) // TODO : front()?
            {
                auto endpoint = url::detail::url_parser(std::move(token), violation.url());
                break_if (!endpoint.has_value());

                using namespace ext::literals;
                auto request = std::make_unique<fetch::detail::request_t>();
                request->method = u"POST";
                request->url = std::make_shared<url::detail::url_t>(violation.url()); // TODO
                request->origin = e.cpp.settings()->origin;
                request->window = fetch::detail::window_t::NO_WINDOW;
                request->client = e.js.settings();
                request->destination = fetch::detail::destination_t::REPORT;
                request->initiator = fetch::detail::initiator_t::_;
                request->credentials_mode = fetch::detail::credentials_t::SAME_ORIGIN;
                request->keep_alive = true;
                request->header_list = fetch::detail::headers_t{ext::make_pair(u"Content-Type"_s16, u"application/csp-report"_s16)};
                // TODO : request->body = (uses a deprecated method)
                request->redirect_mode = fetch::detail::redirect_t::ERROR;

                fetch::detail::fetch(*request);
            }
        }

        if (ranges::contains(violation.policy->directive_set | ranges::views::keys, u"report-to"))
        {
            auto directive = *ranges::find_if(violation.policy->directive_set, BIND_FRONT(ext::pair_key_matches, u"report-to"));

            auto body = std::make_unique<csp::csp_violation_report_body>();
            body->d_func()->document_url = strip_url_for_violation_report(violation.url());
            body->d_func()->referrer = strip_url_for_violation_report(*violation.referrer);
            // TODO : body->d_func()->blocked_url = (uses a deprecated method)
            body->d_func()->effective_directive = violation.effective_directive;
            body->d_func()->original_policy = serialize_csp(*violation.policy);
            body->d_func()->source_file = violation.source_file ? strip_url_for_violation_report(*violation.source_file) : u"";
            body->d_func()->sample = violation.sample;
            body->d_func()->disposition = violation.disposition;
            body->d_func()->status = violation.status;
            body->d_func()->line_number = violation.line_number;
            body->d_func()->column_number = violation.column_number;

            reporting::detail::generate_report(body.get(), u"csp-violation", e.js.settings(), directive.second);
        }
            });
}
