#include "html_meta_element.hpp"
#include "html_meta_element_private.hpp"




html::elements::html_meta_element::html_meta_element()
{
    INIT_PIMPL(html_meta_element);
    HTML_CONSTRUCTOR
}


auto html::elements::html_meta_element::get_name() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_meta_element);
        return d->name;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meta_element::get_content() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_meta_element);
        return d->content;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meta_element::get_media() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_meta_element);
        return d->media;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meta_element::get_http_equiv() const -> detail::http_equiv_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_meta_element);
        return d->http_equiv;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meta_element::set_name(ext::string new_name) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_meta_element);
        return d->name = std::move(new_name);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meta_element::set_content(ext::string new_content) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_meta_element);
        return d->content = std::move(new_content);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meta_element::set_media(ext::string new_media) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_meta_element);
        return d->media = std::move(new_media);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_meta_element::set_http_equiv(detail::http_equiv_t new_http_equiv) -> detail::http_equiv_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_meta_element);
        return d->http_equiv = new_http_equiv;
    CE_REACTIONS_METHOD_EXE
}
