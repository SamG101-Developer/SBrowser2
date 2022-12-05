#include "registration_internals.hpp"

#include "ext/assertion.hpp"

#include "javascript/environment/settings.ixx"


#include "mimesniff/detail/mimetype_internals.hpp"
#include "url/detail/url_internals.hpp"


auto payment::detail::convert_image_object(
        ext::vector_span<detail::image_object_t> input_images)
        -> ext::vector<detail::image_object_t>
{
    auto output_images = ext::vector<detail::image_object_t>{};
    auto e = js::env::env::relevant(input_images);

    decltype(auto) base_url = url::detail::url_serializer(*e.cpp.settings()->api_base_url);

    for (decltype(auto) image: input_images)
    {
        return_if (!mimesniff::detail::valid_mime_type(image[u8"type"].to<ext::string>())) {};
        return_if (!is_valid_sizes(image[u8"sizes"].to<ext::string>())) {};

        auto url = url::detail::url_parser(image[u8"source"].to<ext::string>(), base_url);
        return_if (!url.has_value()) {};
        return_if ((*url).scheme != u8"https") {};

        image[u8"source"] = std::move(url::detail::url_serializer(*url));
        output_images.push_back(image);
    }

    return output_images;
}
