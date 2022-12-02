#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_IMAGE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_IMAGE_INTERNALS_HPP

#include "ext/concepts.ixx"
#include "ext/optional.hpp"
#include "ext/set.hpp"
#include "ext/tuple.ixx"

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(url)

namespace html::elements {class html_element;}
namespace html::elements {class html_image_element;}
namespace html::elements {class html_link_element;}


namespace html::detail
{
    auto decode(
            elements::html_image_element* element)
            -> void;

    auto is_available(
            image_request_t& request)
            -> ext::boolean;

    auto is_fully_decodable(
            image_request_t& request)
            -> ext::boolean;

    auto determine_density_corrected_intrinsic_width_and_height(
            elements::html_image_element* element)
            -> void;

    auto uses_srcset_or_picture(
            elements::html_image_element* element)
            -> ext::boolean;

    auto update_image_data(
            elements::html_image_element* element,
            ext::boolean restart_animation_flag = false)
            -> void;

    auto abort_image_request(
            image_request_t& request)
            -> void;

    auto upgrade_pending_request_to_current_request(
            elements::html_image_element* element)
            -> void;

    auto prepare_image_for_presentation(
            image_request_t& request,
            elements::html_image_element* element)
            -> void;

    auto select_image_source(
            elements::html_image_element* element)
            -> ext::tuple<url::detail::url_t, double>;

    auto select_image_source_from_source_set(
            ext::set<image_source_t*>& source_set)
            -> ext::tuple<url::detail::url_t, double>;

    auto create_source_set(
            const ext::string& default_source,
            const ext::string& src_set,
            const ext::string& sizes)
            -> ext::set<image_source_t*>;

    auto update_source_set(
            ext::type_is<elements::html_image_element*, elements::html_link_element*> auto* element)
            -> void;

    auto parse_source_set_attribute(
            ext::string_view src_set)
            -> ext::set<image_source_t*>;

    auto parse_sizes_attribute(
            ext::string_view sizes)
            -> ext::number<double>;

    auto normalize_source_densities(
            ext::set<image_source_t*>& source_set)
            -> ext::set<image_source_t*>&;

    auto restart_animation(
            elements::html_image_element* element)
            -> void;
}


struct html::detail::image_request_t
{
    state_t state = state_t::UNAVAILABLE;
    std::unique_ptr<url::detail::url_t> url;
    ext::number<int> current_pixel_density {1};
    struct {ext::number<int> width; ext::number<int> height;} preferred_density_corrected_dimensions;
    std::byte image_data[];
};


struct html::detail::available_image_t
{
    ext::tuple<ext::string, fetch::detail::mode_t, url::detail::url_t*> key;
    ext::boolean ignore_higher_layer_caching_flag;

    auto operator==(const ext::tuple<ext::string, fetch::detail::mode_t, url::detail::url_t*>& other) const -> ext::boolean
    {
        return key == other;
    }
};


struct html::detail::image_source_t
{
    std::unique_ptr<url::detail::url_t> url_record;
    ext::string width_descriptor;
    ext::string pixel_density_descriptor;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_IMAGE_INTERNALS_HPP
