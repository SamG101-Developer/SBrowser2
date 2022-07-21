#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_IMAGE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_IMAGE_INTERNALS_HPP

#include "ext/concepts.hpp"
#include "ext/optional.hpp"
#include "ext/tuple.hpp"
#include "url/url.hpp"
#include <cstddef>
namespace html::elements {class html_element;}
namespace html::elements {class html_image_element;}
namespace html::elements {class html_link_element;}
namespace fetch::detail::request_internals {enum class mode_t;}


namespace html::detail::image_internals
{
    struct image_request;
    struct available_image;
    struct image_source;

    enum class state_t {UNAVAILABLE, PARTIALLY_AVAILABLE, COMPLETELY_AVAILABLE, BROKEN};

    auto decode(
            elements::html_image_element* element)
            -> void;

    auto is_available(
            image_request& request)
            -> ext::boolean;

    auto is_fully_decodable(
            image_request& request)
            -> ext::boolean;

    auto determine_density_corrected_intrinsic_width_and_height(
            elements::html_image_element* element)
            -> void;

    auto uses_srcset_or_picture(
            elements::html_image_element* element)
            -> ext::boolean;

    auto update_image_data(
            elements::html_image_element* element,
            ext::boolean_view restart_animation_flag = false)
            -> void;

    auto abort_image_request(
            image_request& request)
            -> void;

    auto upgrade_pending_request_to_current_request(
            elements::html_image_element* element)
            -> void;

    auto prepare_image_for_presentation(
            image_request& request,
            elements::html_image_element* element)
            -> void;

    auto select_image_source(
            elements::html_image_element* element)
            -> ext::tuple<url::url_object, double>;

    auto select_image_source_from_source_set(
            ext::set<image_source*>& source_set)
            -> ext::tuple<url::url_object, double>;

    auto create_source_set(
            const ext::string& default_source,
            const ext::string& src_set,
            const ext::string& sizes)
            -> ext::set<image_source*>;

    auto update_source_set(
            type_is<elements::html_image_element*, elements::html_link_element*> auto* element)
            -> void;

    auto parse_source_set_attribute(
            ext::string_view src_set)
            -> ext::set<image_source*>;

    auto parse_sizes_attribute(
            ext::string_view sizes)
            -> ext::number<double>;

    auto normalize_source_densities(
            ext::set<image_source*>& source_set)
            -> ext::set<image_source*>&;

    auto restart_animation(
            elements::html_image_element* element)
            -> void;
}


struct html::detail::image_internals::image_request
{
    state_t state{state_t::UNAVAILABLE};
    url::url_object url;
    ext::number<int> current_pixel_density {1};
    struct {ext::number<int> width; ext::number<int> height;} preferred_density_corrected_dimensions;
    std::byte image_data[];
};


struct html::detail::image_internals::available_image
{
    ext::tuple<ext::string, fetch::detail::request_internals::mode_t, url::url_object> key;
    ext::boolean ignore_higher_layer_caching_flag;

    auto operator==(const ext::tuple<ext::string, fetch::detail::request_internals::mode_t, url::url_object>& other) const -> ext::boolean
    {
        return key == other;
    }
};


struct html::detail::image_internals::image_source
{
    url::url_object url_record;
    ext::string width_descriptor;
    ext::string pixel_density_descriptor;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_IMAGE_INTERNALS_HPP
