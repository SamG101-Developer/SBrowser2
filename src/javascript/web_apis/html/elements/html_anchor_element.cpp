#include "html_anchor_element.hpp"
#include "html_anchor_element_private.hpp"

#include "javascript/environment/reflection.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/events/event.hpp"

#include "html/detail/link_internals.hpp"


html::elements::html_anchor_element::html_anchor_element()
{
    INIT_PIMPL(html_anchor_element);

    ACCESS_PIMPL(html_anchor_element);
    d->activation_behaviour = [this](dom::events::event* event)
    {
        JS_REALM_GET_RELEVANT(this);
        return_if(!reflect_has_attribute_value(this, u"href", this_relevant));

        ext::string hyperlink_suffix;
        // TODO : distance from mouse click, requires UIEvents
        auto x = ext::number<int>{};
        auto y = ext::number<int>{};
        hyperlink_suffix = char8_t(0x003f) + ext::to_string(x) + char8_t(0x002c) + ext::to_string(y);

        reflect_has_attribute_value(this, u"download", this_relevant) && !download().empty() // TODO : or expressed preference to download
                ? detail::download_hyperlink(this, hyperlink_suffix)
                : detail::follow_hyperlink(this, hyperlink_suffix);
    };

    HTML_CONSTRUCTOR
}


auto html::elements::html_anchor_element::get_target() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_anchor_element);
        return d->target;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_anchor_element::get_download() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_anchor_element);
        return d->download;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_anchor_element::get_ping() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_anchor_element);
        return d->ping;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_anchor_element::get_rel() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_anchor_element);
        return d->rel;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_anchor_element::get_hreflang() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_anchor_element);
        return d->hreflang;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_anchor_element::get_type() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_anchor_element);
        return d->type;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_anchor_element::get_referrer_policy() const -> referrer_policy::detail::referrer_policy_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_anchor_element);
        return d->referrer_policy;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_anchor_element::get_text() const -> ext::string
{
    return dom::detail::descendant_text_content(this);
}


auto html::elements::html_anchor_element::set_target(ext::string new_target) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_anchor_element);
        return d->target = std::move(new_target);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_anchor_element::set_download(ext::string new_download) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_anchor_element);
        return d->download = std::move(new_download);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_anchor_element::set_ping(ext::string new_ping) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_anchor_element);
        return d->ping = std::move(new_ping);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_anchor_element::set_rel(ext::string new_rel) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_anchor_element);
        return d->rel = std::move(new_rel);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_anchor_element::set_hreflang(ext::string new_hreflang) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_anchor_element);
        return d->hreflang = std::move(new_hreflang);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_anchor_element::set_type(ext::string new_type) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_anchor_element);
        return d->type = std::move(new_type);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_anchor_element::set_referrer_policy(referrer_policy::detail::referrer_policy_t new_referrer_policy) -> referrer_policy::detail::referrer_policy_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_anchor_element);
        return d->referrer_policy = new_referrer_policy;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_anchor_element::set_text(ext::string new_text) -> ext::string
{
    return dom::detail::string_replace_all(std::move(new_text), this);
}


auto html::elements::html_anchor_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_anchor_element>{isolate}
            .ctor<>()
            .inherit<html_element>()
            .inherit<mixins::html_hyperlink_element_utils>()
            .property("target", &html_anchor_element::get_target, &html_anchor_element::set_target)
            .property("download", &html_anchor_element::get_download, &html_anchor_element::set_download)
            .property("ping", &html_anchor_element::get_ping, &html_anchor_element::set_ping)
            .property("rel", &html_anchor_element::get_rel, &html_anchor_element::set_rel)
            .property("hreflang", &html_anchor_element::get_hreflang, &html_anchor_element::set_hreflang)
            .property("type", &html_anchor_element::get_type, &html_anchor_element::set_type)
            .property("text", &html_anchor_element::get_text, &html_anchor_element::set_text)
            .property("referrerPolicy", &html_anchor_element::get_referrer_policy, &html_anchor_element::set_referrer_policy)
            .auto_wrap_objects();

    return std::move(conversion);
}

