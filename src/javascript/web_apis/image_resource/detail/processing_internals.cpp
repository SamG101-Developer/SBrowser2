#include "processing_internals.hpp"

#include "fetch/_typedefs.hpp"
#include "javascript/environment/realms_2.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(image_resource)

#include "fetch/detail/body_internals.hpp"
#include "fetch/detail/fetch_internals.hpp"
#include "fetch/detail/request_internals.hpp"
#include "fetch/detail/response_internals.hpp"

#include "dom/detail/exception_internals.hpp"
#include "mimesniff/detail/mimetype_internals.hpp"
#include "url/detail/url_internals.hpp"

#include <v8-container.h>
#include <v8-object.h>
#include <v8-primitive.h>


auto image_resource::detail::process_image_resource_from_api(
        image_resource_options_t&& image_resource)
        -> image_resource_t
{
    JS_REALM_GET_RELEVANT(nullptr);
    decltype(auto) base_url = nullptr_relevant_settings_object->api_base_url;

    auto parsed_mime_type = mimesniff::detail::parse_mime_type(image_resource.try_emplace("type").first->first);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [has_value = parsed_mime_type.has_value()] {return !has_value;},
            "Mime type failed parsing");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [parsed_mime_type = std::move(*parsed_mime_type)] {return !mimesniff::detail::is_image_mime_type(parsed_mime_type);},
            "Mime type must be an image mime type");

    auto image = image_resource_t
    {
        .src = url::detail::url_parser(image_resource.try_emplace("src").first->second),
        // TODO: .sizes =
        .type = *parsed_mime_type,
        .label = serive_accessible_name()
    };

    return image;
}


auto image_resource::detail::process_image_resource_from_json(
        v8::Local<v8::Map> json_object,
        const url::detail::url_t& base)
        -> ext::optional<image_resource_options_t>
{
    JS_REALM_GET_RELEVANT(json_object);

    return_if (!json_object->IsObject() || json_object.IsEmpty()) ext::nullopt;
    return_if (!json_object->Get(json_object_relevant_realm, v8pp::to_v8(json_object_relevant_agent, "src")).ToLocalChecked()->IsString()) ext::nullopt;

    auto image = image_resource_options_t{};
    decltype(auto) base_url = json_object_relevant_settings_object->api_base_url;
    decltype(auto) src = url::detail::url_parser(v8pp::from_v8<ext::string>(json_object_relevant_agent, json_object->Get(json_object_relevant_realm, v8pp::to_v8(json_object_relevant_agent, "src")).ToLocalChecked()), url::detail::url_serializer(base));
    decltype(auto) mime_type = mimesniff::detail::parse_mime_type(v8pp::from_v8<ext::string>(json_object_relevant_agent, json_object->Get(json_object_relevant_realm, v8pp::to_v8(json_object_relevant_agent, "type")).ToLocalChecked()));

    image.insert("src", url::detail::url_serializer(src));
    // TODO : sizes
    image.insert("type", mimesniff::detail::essence(*mime_type));
    image.insert("label", serive_accessible_name());
    return image;
}


auto image_resource::detail::fetching_image_resource(
        const image_resource_t& image,
        ext::optional<const fetch::detail::request_t&> request)
        -> fetch::detail::response_t
{
    JS_REALM_GET_RELEVANT(image);

    auto default_request = fetch::detail::request_t{.url = image.src, .client = v8pp::to_v8(image_relevant_agent, image_relevant_settings_object), .destination = fetch::detail::destination_t::IMAGE};
    decltype(auto) true_request = request.value_or(std::move(default_request));

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [client = true_request.client] {return client.IsEmpty();},
            "Request's client mustn't be null");

    return  fetch::detail::fetch(request);
}


auto image_resource::detail::derive_accessible_name(
        const image_resource_t& image)
        -> ext::string
{
    return_if (!image.label.empty()) image.label;
    return_if (auto name = embedded_accessible_name(image); !name.empty()) name;
    return_if (auto label = external_label(image); !label.empty()) label;
    return "";
}
