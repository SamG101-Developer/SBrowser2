#include "contact_address.hpp"

#include "contact_picker/detail/contact_internals.hpp"


contact_picker::contact_address::contact_address()
        : INIT_PIMPL
{
    bind_get(city);
    bind_get(country);
    bind_get(dependant_locality);
    bind_get(organization);
    bind_get(phone);
    bind_get(postal_code);
    bind_get(recipient);
    bind_get(region);
    bind_get(sorting_code);
    bind_get(address_line);
}


auto contact_picker::contact_address::get_city() const -> decltype(this->city)::value_t
{return d_ptr->city;}


auto contact_picker::contact_address::get_country() const -> decltype(this->country)::value_t
{return d_ptr->country;}


auto contact_picker::contact_address::get_dependant_locality() const -> decltype(this->dependant_locality)::value_t
{return d_ptr->dependent_locality;}


auto contact_picker::contact_address::get_organization() const -> decltype(this->organization)::value_t
{return d_ptr->organization;}


auto contact_picker::contact_address::get_phone() const -> decltype(this->phone)::value_t
{return d_ptr->phone_number;}


auto contact_picker::contact_address::get_postal_code() const -> decltype(this->postal_code)::value_t
{return d_ptr->postal_code;}


auto contact_picker::contact_address::get_recipient() const -> decltype(this->recipient)::value_t
{return d_ptr->recipient;}


auto contact_picker::contact_address::get_region() const -> decltype(this->region)::value_t
{return d_ptr->region;}


auto contact_picker::contact_address::get_sorting_code() const -> decltype(this->sorting_code)::value_t
{return d_ptr->sorting_code;}


auto contact_picker::contact_address::get_address_line() const -> decltype(this->address_line)::value_t
{return d_ptr->address_line;}


auto contact_picker::contact_address::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<contact_address>{isolate}
        .inherit<dom_object>()
        .var("city", &contact_address::city, true)
        .var("country", &contact_address::country, true)
        .var("dependantLocality", &contact_address::dependant_locality, true)
        .var("organization", &contact_address::organization, true)
        .var("phone", &contact_address::phone, true)
        .var("postalCode", &contact_address::postal_code, true)
        .var("recipient", &contact_address::recipient, true)
        .var("region", &contact_address::region, true)
        .var("sortingCode", &contact_address::sorting_code, true)
        .var("addressLine", &contact_address::address_line, true)
        .auto_wrap_objects();

    return std::move(conversion);
}
