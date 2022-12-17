module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.contact_picker.contact_address;
import apis._.dom_object;

import ext.string;
import ext.vector;
import ext.tuple;
import ext.span;

import js.env.module_type;


DEFINE_PUBLIC_CLASS(contact_picker, contact_address) final
        : public virtual dom_object
{
public constructors:
    contact_address();
    MAKE_PIMPL(contact_address);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(city, ext::string_view);
    DEFINE_GETTER(country, ext::string_view);
    DEFINE_GETTER(dependant_locality, ext::string_view);
    DEFINE_GETTER(organization, ext::string_view);
    DEFINE_GETTER(phone, ext::string_view);
    DEFINE_GETTER(postal_code, ext::string_view);
    DEFINE_GETTER(recipient, ext::string_view);
    DEFINE_GETTER(region, ext::string_view);
    DEFINE_GETTER(sorting_code, ext::string_view);
    DEFINE_GETTER(address_line, ext::vector_span<ext::string>);
};
