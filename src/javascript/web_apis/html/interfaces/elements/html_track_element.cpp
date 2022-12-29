#include "html_track_element.hpp"
#include "html_track_element_private.hpp"




auto html::elements::html_track_element::get_kind() const -> detail::track_element_kind_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_track_element);
        return d->kind;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_track_element::get_src() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_track_element);
        return d->src;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_track_element::get_srclang() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_track_element);
        return d->srclang;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_track_element::get_label() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_track_element);
        return d->label;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_track_element::get_default_() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_track_element);
        return d->default_;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_track_element::get_ready_state() const -> ext::number<ushort>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_track_element);
        return d->ready_state;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_track_element::get_track() const -> html::basic_media::text_track*
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_track_element);
        return d->track.get();
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_track_element::set_kind(detail::track_element_kind_t new_kind) -> detail::track_element_kind_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_track_element);
        return d->kind = std::move(new_kind);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_track_element::set_src(ext::string new_src) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_track_element);
        return d->src = std::move(new_src);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_track_element::set_srclang(ext::string new_srclang) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_track_element);
        return d->srclang = std::move(new_srclang);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_track_element::set_label(ext::string new_label) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_track_element);
        return d->label = std::move(new_label);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_track_element::set_default_(ext::boolean new_default_) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_track_element);
        return d->default_ = new_default_;
    CE_REACTIONS_METHOD_EXE
}
