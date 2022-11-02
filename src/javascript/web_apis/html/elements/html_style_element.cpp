#include "html_style_element.hpp"
#include "html_style_element_private.hpp"

#include "dom/detail/customization_internals.hpp"


html::elements::html_style_element::html_style_element()
{
    INIT_PIMPL(html_style_element);
    HTML_CONSTRUCTOR;
}


auto html::elements::html_style_element::get_disabled() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        decltype(auto) style_sheet = css::detail::associated_stylesheet(this);
        return !style_sheet || style_sheet->d_func()->disabled_flag;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_style_element::get_media() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_style_element);
        return d->media;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_style_element::get_blocking() const -> ext::vector_span<detail::blocking_t>
{
    ACCESS_PIMPL(const html_style_element);
    return d->blocking;
}


auto html::elements::html_style_element::set_disabled(ext::boolean new_disabled) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        decltype(auto) style_sheet = css::detail::associated_stylesheet(this);
        return_if (!style_sheet) false;
        return style_sheet->d_func()->disabled_flag = new_disabled;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_style_element::set_media(ext::string new_media) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_style_element);
        return d->media = std::move(new_media);
    CE_REACTIONS_METHOD_EXE
}
