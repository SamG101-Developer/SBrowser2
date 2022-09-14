#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_IMAGE_DATA_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_IMAGE_DATA_HPP

#include "dom_object.hpp"
#include "html/mixins/serializable.hpp"
namespace html::canvasing {class image_data;}

#include USE_INNER_TYPES(html)


class html::canvasing::image_data
        : public virtual dom_object
        , public mixins::serializable
{
public constructors:
    image_data() = default;
    image_data(ext::number<ulong> sw, ext::number<ulong> sh, detail::image_data_settings_t&& = {});
    image_data(ext::vector<ext::number<uchar>>&& data, ext::number<ulong> sw, ext::number<ulong> sh, detail::image_data_settings_t&& = {});

public js_properties:
    ext::property<ext::number<ulong>> width;
    ext::property<ext::number<ulong>> height;
    ext::property<std::unique_ptr<ext::vector<ext::number<uchar>>>> data;
    ext::property<detail::predefined_color_space_t> color_space;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
    auto m_serialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> void override;
    auto m_deserialize(ext::map<ext::string, ext::any> &serialized, ext::boolean for_storage) -> image_data* override;

private cpp_properties:
    ext::vector<detail::color_t> m_canvas_pixel_array_buffer;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_IMAGE_DATA_HPP
