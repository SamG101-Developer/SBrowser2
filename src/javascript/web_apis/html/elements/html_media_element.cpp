#include "html_media_element.hpp"
#include "html_media_element_private.hpp"

#include "dom/detail/customization_internals.hpp"


auto html::elements::html_media_element::get_error() const -> basic_media::media_error*
{
    ACCESS_PIMPL(const html_media_element);
    return d->error.get();
}


auto html::elements::html_media_element::get_src() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_media_element);
        return d->src;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_media_element::get_src_object() const -> detail::media_provider_t
{
    ACCESS_PIMPL(const html_media_element);
    return d->assigned_media_provider_object;
}


auto html::elements::html_media_element::get_current_src() const -> ext::string_view
{
    ACCESS_PIMPL(const html_media_element);
    return d->current_src;
}


auto html::elements::html_media_element::get_cross_origin() const -> detail::cross_origin_settings_attribute_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_media_element);
        return d->cross_origin;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_media_element::get_network_state() const -> ext::number<ushort>
{
    ACCESS_PIMPL(const html_media_element);
    return d->network_state;
}


auto html::elements::html_media_element::get_preload() const -> detail::preload_t
{
    ACCESS_PIMPL(const html_media_element);
    return d->preload;
}
