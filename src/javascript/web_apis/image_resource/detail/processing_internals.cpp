#include "processing_internals.hpp"

#include "ext/expected.hpp"
#include "environment/environment_settings.hpp"

#include "javascript/environment/environment_settings.hpp"
#include "javascript/environment/realms.hpp"

#include INCLUDE_INNER_TYPES(image_resource)

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "fetch/_typedefs.hpp"
#include "fetch/detail/body_internals.hpp"
#include "fetch/detail/fetch_internals.hpp"
#include "fetch/detail/request_internals.hpp"
#include "fetch/detail/response_internals.hpp"

#include "mimesniff/detail/mimetype_internals.hpp"
#include "url/detail/url_internals.hpp"

#include <v8-container.h>
#include <v8-object.h>
#include <v8-primitive.h>


auto image_resource::detail::process_image_resource_from_api(
        image_resource_options_t&& image_resource)
        -> ext::expected<image_resource_options_t, ext::failure_t>
{
    using enum v8_primitive_error_t;

    auto e = js::env::env::relevant(nullptr);
    decltype(auto) base_url = *e.cpp.settings()->api_base_url;
    decltype(auto) parsed_mime_type = mimesniff::detail::parse_mime_type(image_resource.try_emplace("type").first->first);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [has_value = parsed_mime_type.has_value()] {return !has_value;},
            u8"Mime type failed parsing");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [parsed_mime_type = std::move(*parsed_mime_type)] {return !mimesniff::detail::is_image_mime_type(parsed_mime_type);},
            u8"Mime type must be an image mime type");

    auto image = image_resource_t
    {
        .src = url::detail::url_parser(image_resource.try_emplace(u8"src").first->second),
        // TODO: .sizes =
        .type = *parsed_mime_type,
        .label = serive_accessible_name()
    };

    return image;
}


auto image_resource::detail::process_image_resource_from_json(
        v8::Local<v8::Map> json_object,
        const url::detail::url_t& base)
        -> ext::expected<image_resource_options_t, ext::failure_t>
{
    auto e = js::env::env::relevant(json_object);
    return_if (!json_object->IsObject() || json_object.IsEmpty()) ext::failure_t{};
    return_if (!json_object->Get(e.js.realm(), v8pp::to_v8(e.js.agent(), u8"src")).ToLocalChecked()->IsString()) ext::failure_t{};

    auto image = image_resource_options_t{};
    decltype(auto) base_url = *e.cpp.settings()->api_base_url;
    decltype(auto) src = url::detail::url_parser(v8pp::from_v8<ext::string>(e.js.egent(), json_object->Get(e.js.realm(), v8pp::to_v8(e.js.agent, u8"src")).ToLocalChecked()), url::detail::url_serializer(base));
    decltype(auto) mime_type = mimesniff::detail::parse_mime_type(v8pp::from_v8<ext::string>(e.js.egent(), json_object->Get(e.js.realm(), v8pp::to_v8(e.js.agent(), u8"type")).ToLocalChecked()));

    image.insert(u8"src", url::detail::url_serializer(src));
    // TODO : sizes
    image.insert(u8"type", mimesniff::detail::essence(*mime_type));
    image.insert(u8"label", serive_accessible_name());
    return image;
}


auto image_resource::detail::fetching_image_resource(
        const image_resource_t& image,
        ext::optional<const fetch::detail::request_t&> request)
        -> fetch::detail::response_t
{
    using enum v8_primitive_error_t;

    auto e = js::env::env::relevant(image);
    auto default_request = fetch::detail::request_t{.url = image.src, .client = e.js.settings(), .destination = fetch::detail::destination_t::IMAGE};
    decltype(auto) true_request = request.value_or(std::move(default_request));

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [client = true_request.client] {return client.IsEmpty();},
            u8"Request's client mustn't be null");

    return  fetch::detail::fetch(request);
}


auto image_resource::detail::derive_accessible_name(
        const image_resource_t& image)
        -> ext::string
{
    return_if (!image.label.empty()) image.label;
    return_if (auto name = embedded_accessible_name(image); !name.empty()) name;
    return_if (auto label = external_label(image); !label.empty()) label;
    return u8"";
}
