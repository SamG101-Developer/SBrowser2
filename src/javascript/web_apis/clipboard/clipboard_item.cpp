#include "clipboard_item.hpp"

#include "ext/ranges.hpp"

#include "clipboard/_typedefs.hpp"

#include "dom/detail/exception_internals.hpp"

#include "file_api/blob.hpp"

#include "mimesniff/detail/mimetype_internals.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/transform.hpp>


clipboard::clipboard_item::clipboard_item(
        ext::map<ext::string, detail::clipboard_item_data_t>&& items,
        ext::map<ext::string, ext::any>&& options)
{
    bind_get(presentation_style);
    bind_get(types);

    dom::detail::exception_internals::throw_v8_exception<V8_TYPE_ERROR>(
            [items = std::move(items)] {return items.empty();},
            "Items can not be en empty dictionary");

    using detail::presentation_style_t;

    options.try_emplace("presentationStyle", presentation_style_t::UNSPECIFIED);
    m_clipboard_item = detail::clipboard_item_t {.presentation_style = options.at("presentation_style").to<presentation_style_t>()};

    for (const auto& [key, value]: items)
    {
        auto mime_type = mimesniff::detail::mimetype_internals::parse_mime_type(key);

        dom::detail::exception_internals::throw_v8_exception<V8_TYPE_ERROR>(
                [&mime_type] {return !mime_type.has_value();},
                "Failure whilst parsing the mime type");

        dom::detail::exception_internals::throw_v8_exception<V8_TYPE_ERROR>(
                [this, &mime_type] {return ranges::contains(m_clipboard_item.list_of_representations | ranges::views::transform_to_attr(&detail::representation_t::mime_type), mime_type);},
                "Items can not be en empty dictionary");

        detail::representation_t representation{.data = value, .mime_type = std::move(*mime_type)};
        m_clipboard_item.list_of_representations.emplace_back(representation);
        m_types_array.emplace_back(mimesniff::detail::mimetype_internals::serialize_mime_type(*mime_type));
    }
}


auto clipboard::clipboard_item::get_type(
        ext::string&& type)
        -> std::promise<file_api::blob*>
{
    JS_REALM_GET_RELEVANT(this);

    auto mime_type = mimesniff::detail::mimetype_internals::parse_mime_type(std::move(type));

    dom::detail::exception_internals::throw_v8_exception<V8_TYPE_ERROR>(
            [&mime_type] {return !mime_type.has_value();},
            "Failure whilst parsing the mime type");

    decltype(auto) item_type_list = m_clipboard_item.list_of_representations;
    std::promise<file_api::blob*> promise;

    for (const auto& representation: item_type_list)
    {
        continue_if (representation.mime_type != *mime_type);
        auto representation_data_promise = representation.data;
        // TODO
    }
}


auto clipboard::clipboard_item::get_presentation_style()
        const -> detail::presentation_style_t
{
    return m_clipboard_item.presentation_style;
}


auto clipboard::clipboard_item::get_types()
        const -> ext::vector<ext::string>
{
    return m_types_array;
}
