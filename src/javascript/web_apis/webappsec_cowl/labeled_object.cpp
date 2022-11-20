#include "labeled_object.hpp"
#include "labeled_object_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "webappsec_cowl/detail/algorithm_internals.hpp"
#include "webappsec_cowl/detail/cowl_internals.hpp"

#include "html/detail/serialization_internals.hpp"


template <html::concepts::is_serializable T>
webappsec::cowl::labeled_object::labeled_object(T* object, detail::ci_label_t&& labels)
{
    INIT_PIMPL(labeled_object);
    auto object_clone = html::detail::structured_clone(object);
    auto confidentiality = labels[u"confidentiality"].template to<label*>();
    auto integrity = labels[u"integrity"].template to<label*>();

    auto e = js::env::env::relevant(this); // TODO : env
    confidentiality = confidentiality ?: detail::current_confidentially_label(e);
    integrity = integrity ?: detail::current_integrity_label(e);

    using enum dom::detail::dom_exception_error_t;
    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [&confidentiality, &integrity] {return !detail::write_check(confidentiality, integrity);},
            u8"write-check failed with given confidentiality and integrity");

    ACCESS_PIMPL(labeled_object);
    d->confidentiality_label = confidentiality;
    d->integrity_label = integrity;
    d->protected_object = std::move(object_clone);

}


auto webappsec::cowl::labeled_object::get_confidentiality() const -> label*
{
    ACCESS_PIMPL(const labeled_object);
    return d->confidentiality_label.get();
}


auto webappsec::cowl::labeled_object::get_integrity() const -> label*
{
    ACCESS_PIMPL(const labeled_object);
    return d->integrity_label.get();
}


auto webappsec::cowl::labeled_object::get_protected_object() const -> void*
{
    using enum dom::detail::dom_exception_error_t;
    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [e = js::env::env::current()] {return !e.cpp.settings()->is_secure_context;},
            u8"context must be secure when trying to get the protected object");

    ACCESS_PIMPL(const labeled_object);
    detail::context_tainting(d->confidentiality_label.get(), d->integrity_label.get());
    return d->protected_object.get();
}
