#include "contact_address.hpp"
#include "contact_address_private.hpp"

#include "contact_picker/detail/contact_internals.hpp"


contact_picker::contact_address::contact_address()
{
    INIT_PIMPL(contact_address);
}


auto contact_picker::contact_address::get_city() const -> ext::string_view
{
    ACCESS_PIMPL(const contact_address);
    return d->city;
}


auto contact_picker::contact_address::get_country() const -> ext::string_view
{
    ACCESS_PIMPL(const contact_address);
    return d->country;
}


auto contact_picker::contact_address::get_dependant_locality() const -> ext::string_view
{
    ACCESS_PIMPL(const contact_address);
    return d->dependent_locality;
}


auto contact_picker::contact_address::get_organization() const -> ext::string_view
{
    ACCESS_PIMPL(const contact_address);
    return d->organization;
}


auto contact_picker::contact_address::get_phone() const -> ext::string_view
{
    ACCESS_PIMPL(const contact_address);
    return d->phone_number;
}


auto contact_picker::contact_address::get_postal_code() const -> ext::string_view
{
    ACCESS_PIMPL(const contact_address);
    return d->postal_code;
}


auto contact_picker::contact_address::get_recipient() const -> ext::string_view
{
    ACCESS_PIMPL(const contact_address);
    return d->recipient;
}


auto contact_picker::contact_address::get_region() const -> ext::string_view
{
    ACCESS_PIMPL(const contact_address);
    return d->region;
}


auto contact_picker::contact_address::get_sorting_code() const -> ext::string_view
{
    ACCESS_PIMPL(const contact_address);
    return d->sorting_code;
}


auto contact_picker::contact_address::get_address_line() const -> ext::vector<ext::string>
{
    ACCESS_PIMPL(const contact_address);
    return d->address_line;
}


auto contact_picker::contact_address::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<contact_address>{isolate}
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

    return std::move(conversion);
}
