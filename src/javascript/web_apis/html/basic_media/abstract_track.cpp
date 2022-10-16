#include "abstract_track.hpp"
#include "abstract_track_private.hpp"

#include "media_source/source_buffer.hpp"


auto html::basic_media::abstract_track::get_id() const -> ext::string_view
{
    ACCESS_PIMPL(const abstract_track);
    return d->id;
}


auto html::basic_media::abstract_track::get_label() const -> ext::string_view
{
    ACCESS_PIMPL(const abstract_track);
    return d->label;
}


auto html::basic_media::abstract_track::get_language() const -> ext::string_view
{
    ACCESS_PIMPL(const abstract_track);
    return d->language;
}


auto html::basic_media::abstract_track::get_kind() const -> html::detail::text_track_kind_t
{
    ACCESS_PIMPL(const abstract_track);
    return d->kind;
}


auto html::basic_media::abstract_track::get_source_buffer() const -> media::source::source_buffer*
{
    ACCESS_PIMPL(const abstract_track);
    return d->source_buffer.get();
}


auto html::basic_media::abstract_track::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<abstract_track>{isolate}
        .inherit<dom_object>()
        .property("id", &abstract_track::get_id)
        .property("kind", &abstract_track::get_kind)
        .property("label", &abstract_track::get_label)
        .property("language", &abstract_track::get_language)
        .auto_wrap_objects();

    return std::move(conversion);
}
