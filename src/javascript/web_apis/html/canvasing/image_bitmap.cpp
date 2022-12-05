#include "image_bitmap.hpp"



#include INCLUDE_INNER_TYPES(dom)

#include "dom/detail/exception_internals.hpp"

#include <v8pp/class.hpp>
#include <QtCore/QIODevice>
#include <QtGui/QImage>


html::canvasing::image_bitmap::image_bitmap()
{
    bind_get(width);
    bind_get(height);
}


html::canvasing::image_bitmap::image_bitmap(
        const html::canvasing::image_bitmap& data_holder)
{
    // Throw a DATA_CLONE_ERR is the origin of the object being copied ('data_holder') doesn't have a clean origin, so
    // that there's no access to clean origin ImageBitmap's from newly created bitmaps.
    dom::detail::throw_v8_exception<DATA_CLONE_ERR>(
            [origin_clean = data_holder.m_origin_clean_flag] {return !origin_clean;},
            "Copied object's origin must be clean");

    m_bitmap_data = data_holder.m_bitmap_data;
}


auto html::canvasing::image_bitmap::operator=(
        const image_bitmap& data_holder)
        -> image_bitmap&
{
    // Throw a DATA_CLONE_ERR is the origin of the object being copied ('data_holder') doesn't have a clean origin, so
    // that there's no access to clean origin ImageBitmap's from newly created bitmaps.
    dom::detail::throw_v8_exception<DATA_CLONE_ERR>(
            [origin_clean = data_holder.m_origin_clean_flag] {return !origin_clean;},
            "Copied object's origin must be clean");

    m_bitmap_data = data_holder.m_bitmap_data;
    return *this;
}


auto html::canvasing::image_bitmap::close()
        -> void
{
    // Set the [[destached]] slot to true, and detach the QPixmap underlying bitmap data.
    s_detached = true;
    m_bitmap_data.detach();
}


auto html::canvasing::image_bitmap::m_serialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage)
        -> void
{
    // Throw a DATA_CLONE_ERR is the origin of the this object doesn't have a clean origin, so that onyl origin clean
    // ImageBitmaps can be serialized.
    dom::detail::throw_v8_exception<DATA_CLONE_ERR>(
            [origin_clean = m_origin_clean_flag] {return !origin_clean;},
            "Origin must be clean");

    // Convert the QPixmap 'm_bitmap_data' into a [const char*] type.
    serialized.insert_or_assign("$BitmapData", reinterpret_cast<const char*>(m_bitmap_data.toImage().constBits()));
}


auto html::canvasing::image_bitmap::m_deserialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage)
        -> serializable*
{
    // The only option that needs to be set when deserializing is the m_bitmap_data QPixmap yte data - this is accessed
    // and the const char* array from 'serialized', which is loaded into the QPixmap.
    m_bitmap_data.loadFromData(QByteArray{serialized["$BitmapData"].to<ext::string>().c_str()});
}


auto html::canvasing::image_bitmap::get_width()
        const -> typename decltype(this->width)::value_t
{
    // Return 0 if the pixmap is detached (there is no underlying bitmap data available), otherwise return the width, in
    // pixels, of the underlying bitmap data.
    return_if (s_detached()) 0;
    return m_bitmap_data.width();
}


auto html::canvasing::image_bitmap::get_height()
        const -> typename decltype(this->height)::value_t
{
    // Return 0 if the pixmap is detached (there is no underlying bitmap data available), otherwise return the height,
    // in pixels, of the underlying bitmap data.
    return_if (s_detached()) 0;
    return m_bitmap_data.height();
}


auto html::canvasing::image_bitmap::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<image_bitmap>{isolate}
        .inherit<dom_object>()
        .function("close", &image_bitmap::close)
        .var("width", &image_bitmap::width, true)
        .var("height", &image_bitmap::height, true)
        .auto_wrap_objects();
}
