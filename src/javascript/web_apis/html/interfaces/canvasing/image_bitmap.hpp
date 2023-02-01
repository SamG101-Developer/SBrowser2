#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_IMAGE_BITMAP_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_IMAGE_BITMAP_HPP


#include "html/mixins/serializable.hpp"
#include "html/mixins/transferable.hpp"
namespace html::canvasing {class image_bitmap;}

#include <QtGui/QPixmap>


class html::canvasing::image_bitmap
        : public virtual dom_object
        , public html::mixins::serializable
{
public constructors:
    image_bitmap();
    TRANSFERABLE_CONSTRUCTION(image_bitmap);
    TRANSFERABLE_ASSIGNMENT(image_bitmap);
    ~image_bitmap() override = default;

private js_methods:
    auto close() -> void;

private js_properties:
    ext::property<ext::number<ulong>> width;
    ext::property<ext::number<ulong>> height;

private js_slots:
    ext::slot<ext::boolean> s_detached;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

    auto m_serialize(ext::map<ext::string, ext::any>& serialized, ext::boolean for_storage) -> void override;
    auto m_deserialize(ext::map<ext::string, ext::any>& serialized, ext::boolean for_storage) -> serializable* override;

private cpp_properties:
    ext::boolean m_origin_clean_flag;
    QPixmap m_bitmap_data;

private js_properties:
    DEFINE_CUSTOM_GETTER(width);
    DEFINE_CUSTOM_GETTER(height);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_CANVASING_IMAGE_BITMAP_HPP
