#include "registration_internals.hpp"

#include "ext/assertion.hpp"

#include "javascript/environment/environment_settings.hpp"
#include "javascript/environment/realms_2.hpp"

#include "mimesniff/detail/mimetype_internals.hpp"
#include "url/detail/url_internals.hpp"


auto payment::detail::convert_image_object(
        ext::vector_span<detail::image_object_t> input_images)
        -> ext::vector<detail::image_object_t>
{
    auto output_images = ext::vector<detail::image_object_t>{};

    JS_REALM_GET_RELEVANT(input_images);
    decltype(auto) settings_object = v8pp::from_v8<javascript::environment::settings_t*>(
            input_images_relevant_agent,
            input_images_relevant_settings_object);

    decltype(auto) base_url = url::detail::url_serializer(*settings_object->api_base_url);

    for (decltype(auto) image: input_images)
    {
        return_if (!mimesniff::detail::valid_mime_type(image["type"].to<ext::string>())) {};
        return_if (!is_valid_sizes(image["sizes"].to<ext::string>())) {};

        auto url = url::detail::url_parser(image["source"].to<ext::string>(), base_url);
        return_if (!url.has_value()) {};
        return_if ((*url).scheme != "https") {};

        image["source"] = std::move(url::detail::url_serializer(*url));
        output_images.push_back(image);
    }

    return output_images;
}
