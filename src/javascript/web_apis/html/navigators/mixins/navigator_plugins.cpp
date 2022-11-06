#include "navigator_plugins.hpp"
#include "navigator_plugins_private.hpp"


auto html::navigators::mixins::navigator_plugins::get_plugins() const -> ranges::any_helpful_view<plugin*>
{
    ACCESS_PIMPL(const navigator_plugins);
    return d->plugin_array | ranges::views::transform(&std::unique_ptr<plugin>::get);
}


auto html::navigators::mixins::navigator_plugins::get_mime_types() const -> ranges::any_helpful_view<mime_type*>
{
    ACCESS_PIMPL(const navigator_plugins);
    return d->mime_type_array | ranges::views::transform(&std::unique_ptr<mime_type>::get);
}
