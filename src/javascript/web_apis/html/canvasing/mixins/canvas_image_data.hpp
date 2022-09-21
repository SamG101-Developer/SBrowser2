#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_IMAGE_DATA_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_IMAGE_DATA_HPP

#include "dom_object.hpp"
namespace html::canvasing::mixins {class canvas_image_data;}

#include INCLUDE_INNER_TYPES(html)
namespace html::canvasing {class image_data;}


class html::canvasing::mixins::canvas_image_data
        : public virtual dom_object
{
public js_methods:
    auto create_image_data(ext::number<long> sw, ext::number<long> sh, detail::image_data_settings_t&& settings = {}) -> image_data;
    auto create_image_data(image_data* data) -> image_data;
    auto get_image_data(ext::number<long> sx, ext::number<long> sy, ext::number<long> sw, ext::number<long> sh, detail::image_data_settings_t&& settings = {}) -> image_data;
    auto put_image_data(image_data* data, ext::number<long> dx, ext::number<long> dy) -> void;
    auto put_image_data(image_data* data, ext::number<long> dx, ext::number<long> dy, ext::number<long> dirty_x, ext::number<long> dirty_y, ext::number<long> dirty_width, ext::number<long> dirty_height) -> void;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_MIXINS_CANVAS_IMAGE_DATA_HPP
