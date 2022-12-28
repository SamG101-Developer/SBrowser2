module;
#include "ext/macros/pimpl.hpp"


export module apis.reporting.types;
import apis.hr_time.types;
import apis.url.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(reporting)
{
    class report;
    class report_body;
    class reporting_observer;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(reporting)
{
    struct endpoint_t;
    struct report_t;
    struct reporting_observer_t;

    enum class delivery_response_t {SUCCESS, REMOVE_ENDPOINT, FAILURE};

    using report_type_t = ext::string;
}


struct reporting::detail::endpoint_t
{
    ext::string name;
    std::unique_ptr<url::detail::url_t> url;
    ext::number<uint> failures;
};


struct reporting::detail::report_t
{
    ext::map<ext::string, ext::any> body;
    std::unique_ptr<url::detail::url_t> url;
    ext::string user_agent;
    ext::string destination;
    report_type_t type;
    hr_time::epoch_time_stamp timestamp;
    ext::number<uint> attempts;
};


struct reporting::detail::reporting_observer_t
{};
