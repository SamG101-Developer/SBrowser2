#include "html_base_element.hpp"
#include "html_base_element_private.hpp"



#include "html/detail/document_internals.hpp"
#include "url/detail/url_internals.hpp"


html::elements::html_base_element::html_base_element()
{
    INIT_PIMPL(html_base_element);
    HTML_CONSTRUCTOR
}


auto html::elements::html_base_element::get_href() const -> ext::string_view
{
    ACCESS_PIMPL(const html_base_element);
    decltype(auto) document = d->node_document;
    decltype(auto) url = d->href;

    auto url_record = url::detail::url_parser(url, detail::fallback_base_url(document), document->d_func()->encoding.get());
    return !url_record.has_value() ? url : url::detail::url_serializer(*url_record);
}


auto html::elements::html_base_element::get_target() const -> ext::string_view
{
    ACCESS_PIMPL(const html_base_element);
    return d->target;
}


auto html::elements::html_base_element::set_href(ext::string new_href) -> ext::string
{
    ACCESS_PIMPL(html_base_element);
    return d->href = std::move(new_href);
}


auto html::elements::html_base_element::set_target(ext::string new_target) -> ext::string
{
    ACCESS_PIMPL(html_base_element);
    return d->target = std::move(new_target);
}


auto html::elements::html_base_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_base_element>{isolate}
        .inherit<html_element>()
        .ctor<>()
        .property("href", &html::elements::html_base_element::get_href, &html::elements::html_base_element::set_href)
        .property("target", &html::elements::html_base_element::get_target, &html::elements::html_base_element::set_target)
        .auto_wrap_objects();

    return std::move(conversion);
}
