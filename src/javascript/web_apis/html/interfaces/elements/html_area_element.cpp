#include "html_area_element.hpp"
#include "html_area_element_private.hpp"




#include "html/detail/link_internals.hpp"
#include "referrer_policy/_typedefs.hpp"


html::elements::html_area_element::html_area_element()
{
    INIT_PIMPL(html_area_element);
    ACCESS_PIMPL(html_area_element);

    d->activation_behaviour = [this, d](dom::events::event* event)
            {
        return_if (d->href.empty());
        !d->download.empty() || detail::user_has_preference_to_download_hyperlink()
                ? detail::download_hyperlink(this, d->href)
                : detail::follow_hyperlink(this, d->href);
            };

    HTML_CONSTRUCTOR
}


auto html::elements::html_area_element::get_alt() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_area_element);
        return d->alt;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::get_coords() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_area_element);
        return d->coords;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::get_shape() const -> detail::area_shape_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_area_element);
        return d->shape;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::get_target() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_area_element);
        return d->href.empty() ? ext::string{} : d->target;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::get_download() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_area_element);
        return d->href.empty() ? ext::string{} : d->download;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::get_ping() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_area_element);
        return d->href.empty() ? ext::string{} : d->ping;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::get_rel() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_area_element);
        return d->href.empty() ? ext::string{} : d->rel;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::get_referrer_policy() const -> referrer_policy::detail::referrer_policy_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_area_element);
        return d->href.empty() ? referrer_policy::detail::referrer_policy_t::_ : d->referrer_policy;
    CE_REACTIONS_METHOD_EXE
}

auto html::elements::html_area_element::set_alt(ext::string new_alt) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_area_element);
        return d->alt = std::move(new_alt);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::set_coords(ext::string new_coords) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_area_element);
        return d->coords = std::move(new_coords);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::set_shape(detail::area_shape_t new_shape) -> detail::area_shape_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_area_element);
        return d->shape = new_shape;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::set_target(ext::string new_target) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_area_element);
        return d->href.empty() ? ext::string{} : d->target = std::move(new_target);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::set_download(ext::string new_download) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_area_element);
        return d->href.empty() ? ext::string{} : d->download = std::move(new_download);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::set_ping(ext::string new_ping) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_area_element);
        return d->href.empty() ? ext::string{} : d->ping = std::move(new_ping);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::set_rel(ext::string new_rel) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_area_element);
        return d->href.empty() ? ext::string{} : d->rel = std::move(new_rel);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::set_referrer_policy(referrer_policy::detail::referrer_policy_t new_referrer_policy) -> referrer_policy::detail::referrer_policy_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_area_element);
        return d->href.empty() ? referrer_policy::detail::referrer_policy_t::_ : d->referrer_policy = new_referrer_policy;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_area_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_area_element>{isolate}
        .inherit<html_element>()
        .ctor<>()
        .property("alt", &html_area_element::get_alt, &html_area_element::set_alt)
        .property("coords", &html_area_element::get_alt, &html_area_element::set_alt)
        .property("shape", &html_area_element::get_alt, &html_area_element::set_alt)
        .property("target", &html_area_element::get_alt, &html_area_element::set_alt)
        .property("download", &html_area_element::get_alt, &html_area_element::set_alt)
        .property("ping", &html_area_element::get_alt, &html_area_element::set_alt)
        .property("rel", &html_area_element::get_alt, &html_area_element::set_alt)
        .property("referrer_policy", &html_area_element::get_alt, &html_area_element::set_alt)
        .auto_wrap_objects();
}
