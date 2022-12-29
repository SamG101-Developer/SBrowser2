#include "mime_type.hpp"
#include "mime_type_private.hpp"


auto html::navigators::mime_type::get_type() const -> ext::string_view
{
    ACCESS_PIMPL(const mime_type);
    return d->type;
}


auto html::navigators::mime_type::get_description() const -> ext::string_view
{
    ACCESS_PIMPL(const mime_type);
    return d->description;
}


auto html::navigators::mime_type::get_suffixes() const -> ext::string_view
{
    ACCESS_PIMPL(const mime_type);
    return d->suffixes;
}
