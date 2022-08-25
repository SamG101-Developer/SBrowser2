#include "html_base_element.hpp"

#include "dom/nodes/document.hpp"
#include "html/detail/document_internals.hpp"
#include "url/detail/url_internals.hpp"


html::elements::html_base_element::html_base_element()
{
    bind_get(href);

    HTML_CONSTRUCTOR
}


auto html::elements::html_base_element::get_href()
        const -> decltype(this->href)::value_t
{
    decltype(auto) document = owner_document();
    decltype(auto) url = *href;

    auto url_record = url::detail::url_parser(detail::fallback_base_url(document), document->m_encoding);
    return !url_record
            ? url
            : url::detail::url_serializer(url_record);
}
