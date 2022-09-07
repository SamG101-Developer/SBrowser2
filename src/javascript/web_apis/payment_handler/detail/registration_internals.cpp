#include "registration_internals.hpp"

#include "ext/assertion.hpp"
#include "javascript/environment/realms_2.hpp"

#include "mimesniff/detail/mimetype_internals.hpp"
#include "url/detail/url_internals.hpp"

#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/to_container.hpp>


auto payment::detail::convert_image_object(
        ext::vector_view<detail::image_object_t*> input_images)
        -> ext::vector<detail::image_object_t*>
{
    JS_REALM_GET_RELEVANT(input_images);
    auto base_url = url::detail::url_serializer(input_images_relevant_settings_object->api_base_url);

    auto image_url_validation =
            [base_url = std::move(base_url)](detail::image_object_t* image)
            {
                auto potential_url = url::detail::url_parser((*image)["src"].to<ext::string>(), base_url);
                ASSERT(potential_url.has_value());
                ASSERT(potential_url->scheme == "https");
                (*image)["src"] = url::detail::url_serializer(*potential_url);
            };

    try
    {
        return input_images
                | ranges::views::for_each([](detail::image_object_t* image) {ASSERT(mimesniff::detail::parse_mime_type((*image)["type"].to<ext::string>()).has_value());})
                | ranges::views::for_each([](detail::image_object_t* image) {ASSERT(is_valid_sizes((*image)["sizes"].to<ext::string>()));})
                | ranges::views::for_each([&image_url_validation](detail::image_object_t* image) {image_url_validation(image);})
                | ranges::to<ext::vector<ext::string>>;
    }
    catch (...)
    {
        return {};
    }
}
