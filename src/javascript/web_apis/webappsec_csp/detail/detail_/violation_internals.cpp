#include "violation_internals.hpp"

#include "file_api/detail/blob_internals.hpp"
#include "url/detail/url_internals.hpp"

#include "webappsec_csp/detail/csp_internals.hpp"


auto webappsec::detail::create_violation_object(
        v8::Local<v8::Object> global_object,
        std::unique_ptr<policy_t> policy,
        ext::string_view directive)
        -> std::unique_ptr<violation_t>
{
    auto violation = std::make_unique<violation_t>();
    violation->global_object = global_object;
    violation->policy = std::move(policy);
    violation->effective_directive = directive;
    violation->resource = std::make_unique<url::detail::url_t>(nullptr);
    return violation;
}


auto webappsec::detail::create_violation_object(
        const fetch::detail::request_t& request,
        std::unique_ptr<policy_t> policy)
        -> std::unique_ptr<violation_t>
{

}
