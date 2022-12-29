module;
#include "ext/macros/macros.hpp"
#include "javascript/macros/expose.hpp"
#include <tuplet/tuple.hpp>
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.contact_picker.contact_address;
import apis.contact_picker.contact_address_private;

import ext.core;
import js.env.module_type;


contact_picker::contact_address::contact_address()
{
    INIT_PIMPL;
}


auto contact_picker::contact_address::get_city() const -> ext::string_view
{
    // The 'city' getter returns the equivalent 'city' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->address->city;
}


auto contact_picker::contact_address::get_country() const -> ext::string_view
{
    // The 'country' getter returns the equivalent 'country' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->address->country;
}


auto contact_picker::contact_address::get_dependant_locality() const -> ext::string_view
{
    // The 'dependant_locality' getter returns the equivalent 'dependant_locality' attribute value that is stored in the
    // private class.
    ACCESS_PIMPL;
    return d->address->dependent_locality;
}


auto contact_picker::contact_address::get_organization() const -> ext::string_view
{
    // The 'organization' getter returns the equivalent 'organization' attribute value that is stored in the private
    // class.
    ACCESS_PIMPL;
    return d->address->organization;
}


auto contact_picker::contact_address::get_phone() const -> ext::string_view
{
    // The 'phone' getter returns the equivalent 'phone' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->address->phone_number;
}


auto contact_picker::contact_address::get_postal_code() const -> ext::string_view
{
    // The 'postal_code' getter returns the equivalent 'postal_code' attribute value that is stored in the private
    // class.
    ACCESS_PIMPL;
    return d->address->postal_code;
}


auto contact_picker::contact_address::get_recipient() const -> ext::string_view
{
    // The 'recipient' getter returns the equivalent 'recipient' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->address->recipient;
}


auto contact_picker::contact_address::get_region() const -> ext::string_view
{
    // The 'region' getter returns the equivalent 'region' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->address->region;
}


auto contact_picker::contact_address::get_sorting_code() const -> ext::string_view
{
    // The 'sorting_code' getter returns the equivalent 'sorting_code' attribute value that is stored in the private
    // class.
    ACCESS_PIMPL;
    return d->address->sorting_code;
}


auto contact_picker::contact_address::get_address_line() const -> ext::vector_span<ext::string>
{
    // The 'address_line' getter returns the equivalent 'address_line' attribute value that is stored in the private
    // class.
    ACCESS_PIMPL;
    return d->address->address_line;
}


auto contact_picker::contact_address::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("city", &contact_address::get_city)
        .property("country", &contact_address::get_country)
        .property("dependantLocality", &contact_address::get_dependant_locality)
        .property("organization", &contact_address::get_organization)
        .property("phone", &contact_address::get_phone)
        .property("postalCode", &contact_address::get_postal_code)
        .property("recipient", &contact_address::get_recipient)
        .property("region", &contact_address::get_region)
        .property("sortingCode", &contact_address::get_sorting_code)
        .property("addressLine", &contact_address::get_address_line)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
