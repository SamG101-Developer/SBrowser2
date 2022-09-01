#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_IMAGE_DATA_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_IMAGE_DATA_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_image_data;}

#include USE_INNER_TYPES(html)
namespace html::canvasing {class image_data;}


class html::canvasing::mixins::canvas_image_data
        : public virtual dom_object
{
public js_methods:
    auto create_image_data(
            const ext::number<long>& sw, const ext::number<long>& sh, detail::image_data_settings_t&& settings = {})
            -> image_data;

    auto create_image_data(
            image_data* data) -> image_data;

    auto get_image_data(
            const ext::number<long>& sx, const ext::number<long>& sy, const ext::number<long>& sw,
            const ext::number<long>& sh, detail::image_data_settings_t&& settings = {}) -> image_data;

    auto put_image_data(
            image_data* data, const ext::number<long>& dx, const ext::number<long>& dy) -> void;

    auto put_image_data(
            image_data* data, const ext::number<long>& dx, const ext::number<long>& dy,
            const ext::number<long>& dirty_x, const ext::number<long>& dirty_y, const ext::number<long>& dirty_width,
            const ext::number<long>& dirty_height) -> void;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_IMAGE_DATA_HPP
