#include "contact_address.hpp"

#include "contact_picker/detail/contact_internals.hpp"


contact_picker::contact_address::contact_address()
        : INIT_PIMPL
{}


auto contact_picker::contact_address::get_city() const -> ext::string
{return d_ptr->city;}


auto contact_picker::contact_address::get_country() const -> ext::string
{return d_ptr->country;}


auto contact_picker::contact_address::get_dependant_locality() const -> ext::string
{return d_ptr->dependent_locality;}


auto contact_picker::contact_address::get_organization() const -> ext::string
{return d_ptr->organization;}


auto contact_picker::contact_address::get_phone() const -> ext::string
{return d_ptr->phone_number;}


auto contact_picker::contact_address::get_postal_code() const -> ext::string
{return d_ptr->postal_code;}


auto contact_picker::contact_address::get_recipient() const -> ext::string
{return d_ptr->recipient;}


auto contact_picker::contact_address::get_region() const -> ext::string
{return d_ptr->region;}


auto contact_picker::contact_address::get_sorting_code() const -> ext::string
{return d_ptr->sorting_code;}


auto contact_picker::contact_address::get_address_line() const -> ext::vector<ext::string>
{return d_ptr->address_line;}


auto contact_picker::contact_address::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
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
