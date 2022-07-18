#include "html_base_element.hpp"

#include "html/detail/document_internals.hpp"


html::elements::html_base_element::html_base_element()
{
    bind_get(href);

    HTML_CONSTRUCTOR
}


auto html::elements::html_base_element::get_href() const -> ext::string
{
    auto* document = owner_document();
    auto& url = *href;

    auto url_record = url::detail::parsing_serializing_internals::::parse(detail::document_internals::fallback_base_url(document), document->m_encoding);
    return !url_record
            ? url
            : url::detail::parsing_serializing_internals::serialize(url_record);
}
