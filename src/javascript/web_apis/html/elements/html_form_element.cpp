#include "html_form_element.hpp"
#include "html_form_element_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"


html::elements::html_form_element::html_form_element()
{
    INIT_PIMPL(html_form_element);
    HTML_CONSTRUCTOR;
}


auto html::elements::html_form_element::submit() -> void
{
    detail::submit(this, this, true);
}


auto html::elements::html_form_element::request_submit(html::elements::html_element* submitter)
{
    using enum dom::detail::dom_exception_error_t;
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [submitter] {return submitter && !detail::is_submittable_button(submitter);},
            u8"Cannot be submitted from an element that isn't a submittable-button");

    dom::detail::throw_v8_exception<NOT_FOUND_ERR>(
            [submitter] {return submitter && detail::form_owner(submitter) != this;},
            u8"The submitters form owner must be this HTMLFormElement");

    detail::submit(this, submitter ?: this);
}


auto html::elements::html_form_element::reset() -> void
{
    ACCESS_PIMPL(html_form_element);
    return_if (d->locked_for_reset);

    d->locked_for_reset = true;
    details::reset(this);
    d->locked_for_reset = false;
}
