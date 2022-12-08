#include "payment_request.hpp"
#include "payment_request_private.hpp"



#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(payment_method_id)







#include "html/detail/document_internals.hpp"
#include "html/detail/task_internals.hpp"

#include "payment_method_id/detail/identifier_internals.hpp"
#include "url/detail/url_internals.hpp"

#include <range/v3/to_container.hpp>


payment::request::payment_request::payment_request(
        ext::vector_span<detail::payment_method_data_t*> method_data,
        detail::payment_method_init_t&& details)
{
//    INIT_PIMPL(payment_request);
//    ACCESS_PIMPL(payment_request);
//    using enum dom::detail::dom_exception_error_t;
//
//    JS_REALM_GET_CURRENT;
//    dom::detail::throw_v8_exception_formatted<SECURITY_ERR>(
//            [document = v8pp::from_v8<dom::nodes::window*>(current_agent, current_global_object)->d_func()->document] {return html::detail::allowed_to_use(document, "payment");},
//            "Document not allowed to use the 'payment' feature");
//
//    d->id = ext::uuid::from_string(details.try_emplace("id", ext::uuid_system_generator{}().as_bytes() | ranges::to<ext::string>()).first->second()->to<ext::string>());
//    auto serialized_method_data = ext::vector<ext::string>{};
//
//    {
//        dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
//                [length = method_data.size()] {return length <= 0;},
//                "Must have at least one payment method");
//
//        auto seen_pmis = ext::set<detail::payment_method_identifier_t>{};
//
//        for (decltype(auto) payment_method: method_data)
//        {
//            auto supported_methods = payment_method["supportedMethods"].to<ext::string>();
//            dom::detail::throw_v8_exception<V8_RANGE_ERROR>(
//                    [validation = detail::validate_payment_method_identifier(supported_methods)] {return !validation;},
//                    "Invalid 'supportedMethods'");
//
//            auto pmi = url::detail::basic_url_parser(supported_methods).value_or(supported_methods);
//            dom::detail::throw_v8_exception<V8_RANGE_ERROR>(
//                    [validation = seen_pmis.contains(pmi)] {return !validation;},
//                    "Cannot have duplicate 'pmi'");
//
//            seen_pmis.emplace(std::move(pmi));
//            // TODO (JSON)
//        }
//    }
}


auto payment::request::payment_request::abort()
        -> ext::promise<void>
{
    ACCESS_PIMPL(payment_request);
    using enum dom::detail::dom_exception_error_t;
    using namespace ext::literals;

    auto promise = ext::promise<void>{};
    return_if (d->response && d->response->d_func()->retry_promise) promise.reject(dom::other::dom_exception{"Cannot abort if the response is retrying"_es, INVALID_STATE_ERR});
    return_if (d->state != detail::state_t::INTERACTIVE) promise.reject(dom::other::dom_exception{"Cannot abort state isn't interactive"_es, INVALID_STATE_ERR});

    GO [d, &promise]
    {
        // TODO : abort
        dom::detail::queue_task(html::detail::user_interaction_task_source,
                [d, &promise]
                {
            // TODO : can;t abort? -> error
            d->state = detail::state_t::CLOSED;
            d->accept_promise.reject(dom::other::dom_exception{"Aborted"_es, ABORT_ERR});
            return promise.resolve();
                });
    };
}


auto payment::request::payment_request::get_id() const -> ext::string
{
    ACCESS_PIMPL(const payment_request);
    return uuids::to_string(d->id) | ranges::to<ext::string>(); // TODO : ext:: ?
}
