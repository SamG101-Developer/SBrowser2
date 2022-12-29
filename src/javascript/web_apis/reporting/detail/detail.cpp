module;
#include <tl/optional.hpp>


module apis.reporting.detail;
import apis.reporting.types;

import apis.dom.window;
import apis.dom.window_private;

import apis.hr_time.detail;

import apis.html.concepts;

import apis.url.types;

import ext.core;
import js.env.realms;


template <html::concepts::is_serializable T>
auto reporting::detail::generate_report(
        T* data,
        ext::string&& type,
        ext::string&& destination,
        const js::env::env& object,
        ext::optional<url::detail::url_t&> url)
        -> std::unique_ptr<report_t>
{
    // Create a new internal report struct and set the attributes to the parameter values (or attributes of them), the
    // 'timestamp' to the current time, and the number of attempts to 0.
    auto report = std::make_unique<report_t>();
    report->body = data->_serialize();
    report->user_agent = object.cpp.global<dom::window>()->d_func()->navigator.get();
    report->destination = std::move(destination);
    report->type = std::move(type);
    report->timestamp = hr_time::detail::current_hr_time(object);
    report->attempts = 0;

    // Get the url from the optional 'url' parameter, erase the 'username' and 'password' fields, set the 'report.url'
    // to the serialziation of 'url', and return the 'report'.
    auto parsed_url = url.has_value() ? *url : *object.cpp.settings->creation_url;
    parsed_url.d_func()->username = u"";
    parsed_url.d_func()->password = u""; // TODO : null?
    report.url = url::detail::url_serializer(parsed_url, true);
    return report;
}


auto reporting::detail::serialize_list_or_reports_to_json(
        ext::span<report_t*> reports)
        -> ext::string
{
    // Create a collection of serialized data that will be collected into a finel serialized string.
    auto collection = ext::vector<ext::map<ext::string, ext::any>>{};

    // Iterate over each 'report' in 'reports' to serialize each report in the list.
    for (decltype(auto) report: reports)
    {
        // Incrment the number of attempts on the 'report' by 1. Serialize the 'report' into 'collections' by viewing
        // certain attributes and creating a serialization map. Calculate the "age" by taking the difference between
        // the current time and the time that the report was created at.
        report->attempts += 1;
        collection.emplace_back({
            {u"age", hr_time::detail::current_time() - report->timestamp},
            {u"type", ext::string_view{report->type}},
            {u"url", *report->url},
            {u"user_agent", ext::string_view{report->user_agent}},
            {u"body", ext::span{report->body}}});
    }

    // Return the combination of the items in 'collections'.
    return infra::detail::serialize_infra_value_to_json_bytes(collection);
}
