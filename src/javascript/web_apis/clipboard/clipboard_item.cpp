#include "clipboard_item.hpp"

#include "clipboard/_typedefs.hpp"

#include "dom/detail/exception_internals.hpp"

#include "file_api/blob.hpp"


clipboard::clipboard_item::clipboard_item(
        ext::map<ext::string, detail::clipboard_item_data_t>&& items,
        ext::map<ext::string, ext::any>&& options)
{
    dom::detail::exception_internals::throw_v8_exception<V8_TYPE_ERROR>(
            [&items] {return items.empty();},
            "Items can not be en empty dictionary");

    using detail::presentation_style_t;

    options.try_emplace("presentationStyle", presentation_style_t::UNSPECIFIED);
    m_clipboard_item = detail::clipboard_item_t {.presentation_style = options.at("presentation_style").to<presentation_style_t>()};

    for (const auto& [key, value]: items)
    {

    }
}
