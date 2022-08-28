#include "contact_address.hpp"

#include "contact_picker/detail/contact_internals.hpp"


auto contact_picker::contact_address::get_city() const -> decltype(this->city)::value_t
{return m_address->city;}


auto contact_picker::contact_address::get_country() const -> decltype(this->country)::value_t
{return m_address->country;}


auto contact_picker::contact_address::get_dependant_locality() const -> decltype(this->dependant_locality)::value_t
{return m_address->dependent_locality;}


auto contact_picker::contact_address::get_organization() const -> decltype(this->organization)::value_t
{return m_address->organization;}


auto contact_picker::contact_address::get_phone() const -> decltype(this->phone)::value_t
{return m_address->phone_number;}


auto contact_picker::contact_address::get_postal_code() const -> decltype(this->postal_code)::value_t
{return m_address->postal_code;}


auto contact_picker::contact_address::get_recipient() const -> decltype(this->recipient)::value_t
{return m_address->recipient;}


auto contact_picker::contact_address::get_region() const -> decltype(this->region)::value_t
{return m_address->region;}


auto contact_picker::contact_address::get_sorting_code() const -> decltype(this->sorting_code)::value_t
{return m_address->sorting_code;}


auto contact_picker::contact_address::get_address_line() const -> decltype(this->address_line)::value_t
{return m_address->address_line;}
