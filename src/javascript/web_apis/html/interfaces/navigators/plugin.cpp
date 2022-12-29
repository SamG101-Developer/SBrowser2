#include "plugin.hpp"
#include "plugin_private.hpp"


auto html::navigators::plugin::get_name() const -> ext::string_view
{
    ACCESS_PIMPL(const plugin);
    return d->name;
}


auto html::navigators::plugin::get_filename() const -> ext::string_view
{
    ACCESS_PIMPL(const plugin);
    return d->filename;
}


auto html::navigators::plugin::get_description() const -> ext::string_view
{
    ACCESS_PIMPL(const plugin);
    return d->description;
}
