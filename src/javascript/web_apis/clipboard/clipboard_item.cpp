#include "clipboard_item.hpp"

#include "ext/pimpl.ixx"


#include "dom/detail/exception_internals.hpp"
#include "dom/other/dom_exception.hpp"

#include "clipboard/detail/clipboard_internals.hpp"
#include "file_api/blob.hpp"
#include "mimesniff/detail/mimetype_internals.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/transform.hpp>


clipboard::clipboard_item::clipboard_item()
        : INIT_PIMPL
{
    bind_get(presentation_style);
    bind_get(types);
}


clipboard::clipboard_item::clipboard_item(
        ext::map<ext::string, detail::clipboard_item_data_t>&& items,
        ext::map<ext::string, ext::any>&& options)
        : clipboard_item{}
{
    // A ClipboardItem can not be created with an empty list of 'items', because the ClipboardItem has to represent some
    // form of data. The error is a JavaScript TypeError.
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [items = std::move(items)] {return items.empty();},
            "Items can not be en empty dictionary");

    using detail::presentation_style_t;

    // Initialize the internal clipboard item to an object whose presentation style is dictated by by the 'options'
    // dictionary, with a default of UNSPECIFIED.
    options.try_emplace("presentationStyle", presentation_style_t::UNSPECIFIED);
    d_ptr->presentation_style = options.at("presentation_style").to<presentation_style_t>();

    // Iterate over each mime_type and item_data in the 'items' map.
    for (const auto& [key, value]: items)
    {
        // Parse the mime type into its designated type (also wrapped with optional in-case of a failure in parsing)
        auto mime_type = mimesniff::detail::parse_mime_type(key);

        // Throw a JavaScript TypeError if the 'mime_type' parsing failed (mime type is required for this method), or if
        // the current clipboard's list of representations doesn't contain the 'mime_type'.
        dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
                [&mime_type] {return !mime_type.has_value();},
                "Failure whilst parsing the mime type");

        dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
                [this, &mime_type] {return ranges::contains(d_ptr->list_of_representations | ranges::views::transform_to_attr(&detail::representation_t::mime_type), mime_type);},
                "The current clipboard item's list of representations must contain the given mimetypes");

        // Create a representation using the 'value' and parsed 'mime_type' value, and append it to the current
        // clipboard's list of representations. Also append a serialization of the 'mime_type' to the types array.
        detail::representation_t representation{.mime_type = std::unique_ptr<decltype(mime_type)::value_type>{&*mime_type}, .data = value};
        d_ptr->list_of_representations.emplace_back(representation);
        d_ptr->types_array.emplace_back(mimesniff::detail::serialize_mime_type(*mime_type));
    }
}


auto clipboard::clipboard_item::get_type(
        ext::string&& type)
        -> ext::promise<file_api::blob*>
{
    // Parse the 'type' into a 'mime_type' using the mime-sniff parser; the 'mime_type' is needed to handle what happens
    // to the 'promise'.
    auto mime_type = mimesniff::detail::parse_mime_type(std::move(type));

    // Throw a JavaScript TypeError if the 'mime_type' parsing failed, because the algorithm can't continue if there
    // isn't a valid 'mime_type'.
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&mime_type] {return !mime_type.has_value();},
            "Failure whilst parsing the mime type");

    ext::promise<file_api::blob*> promise;

    // Iterator over each struct in the 'item_type_list', which is each struct containing a mime type and its associated
    // piece of data.
    for (const auto& representation: d_ptr->list_of_representations)
    {
        // If the representation's mime type doesn't match 'mime_type', then continue -- the algorithm only moves
        // forwards if the mime types are a match. Store the associated data from the representation struct in 'data'.
        continue_if (*representation.mime_type != *mime_type);
        decltype(auto) representation_data_promise = representation.data;

        // React to the 'promise' in different ways, depending on the 'mime_type'.
        promise.react(
                [&promise, mime_type = std::move(*mime_type)]<typename T>(T&& value) mutable
                {
                    // Resolving a promise with T matching ext::string || ext::string_view: create a Blob object with
                    // the bytes set to the 'value' argument (forwarded), and the options dictionary containing a
                    // "type", which is the serialization of 'mime_type'.
                    if constexpr (type_is<T, ext::string, ext::string_view>)
                        promise.template resolve(file_api::blob{std::forward<T>(value), {{"type", mimesniff::detail::serialize_mime_type(std::move(mime_type))}}});
                    
                    // Resolving a promise with T matching Blob: forward the Blob object into the resolve method.
                    else if constexpr (type_is<T, file_api::blob*>)
                        promise.template resolve(std::forward<T>(value));
                },

                [&promise]
                {
                    // Rejecting the promise: create a NOT_FOUND_ERR dom exception, and reject the promise with it.
                    promise.reject(std::move(dom::other::dom_exception{"Error", NOT_FOUND_ERR}));
                }
                );
        
        // Return the promise (always happens at the first matching mime type found from the 'representations'
        return promise;
    }
    
    // If no mime types matches are found, then reject the promise with a NOT_FOUND_ERR, and return the rejected
    // promise.
    promise.reject(std::move(dom::other::dom_exception{"Error", NOT_FOUND_ERR}));
    return promise;
}


auto clipboard::clipboard_item::get_presentation_style() const -> detail::presentation_style_t
{return d_ptr->presentation_style;}


auto clipboard::clipboard_item::get_types() const -> ext::vector<ext::string>
{return d_ptr->types_array;}


auto clipboard::clipboard_item::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<clipboard_item>{isolate}
        .inherit<dom_object>()
        .ctor<ext::map<ext::string, detail::clipboard_item_data_t>&&, ext::map<ext::string, ext::any>&&>()
        .function("getType", &clipboard_item::get_type)
        .var("presentationStyle", &clipboard_item::presentation_style, true)
        .var("types", &clipboard_item::types, true)
        .auto_wrap_objects();

    return std::move(conversion);
}
