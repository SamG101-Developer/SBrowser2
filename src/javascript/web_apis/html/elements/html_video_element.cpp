#include "html_video_element.hpp"
#include "html_video_element_private.hpp"

#include "dom/detail/customization_internals.hpp"
#include "hr_time/detail/time_internals.hpp"

#include "media_playback_quality/video_playback_quality.hpp"
#include "media_playback_quality/video_playback_quality_private.hpp"

#include "url/detail/url_internals.hpp"

#include <qvideowidget.h>


auto html::elements::html_video_element::get_video_playback_quality()
        -> std::unique_ptr<media::playback_quality::video_playback_quality>
{
    ACCESS_PIMPL(const html_video_element);
    auto e = js::env::env::current();

    auto playback_quality = std::make_unique<media::playback_quality::video_playback_quality>();
    playback_quality->d_func()->creation_time = hr_time::detail::current_hr_time(e.js.global());
    playback_quality->d_func()->total_video_frames = d->total_video_frame_count;
    playback_quality->d_func()->dropped_video_frames = d->dropped_video_frame_count;
    return playback_quality;
}


auto html::elements::html_video_element::get_width() const -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_video_element);
        return qobject_cast<QVideoWidget*>(d->media_resource->videoOutput())->width();
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_video_element::get_height() const -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_video_element);
        return qobject_cast<QVideoWidget*>(d->media_resource->videoOutput())->height();
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_video_element::get_poster() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_video_element);
        return url::detail::url_serializer(*d->poster);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_video_element::get_plays_inline() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_video_element);
        return d->plays_inline;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_video_element::set_width(ext::number<ulong> new_width) -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_video_element);
        decltype(auto) video_widget = qobject_cast<QVideoWidget*>(d->media_resource->videoOutput());
        video_widget->setFixedWidth(new_width);
        return video_widget->width();
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_video_element::set_height(ext::number<ulong> new_height) -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_video_element);
        decltype(auto) video_widget = qobject_cast<QVideoWidget*>(d->media_resource->videoOutput());
        video_widget->setFixedHeight(new_height);
        return video_widget->height();
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_video_element::set_poster(ext::string new_poster) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_video_element);
        d->poster = std::make_unique<url::detail::url_t>(url::detail::url_parser(new_poster));
        return url::detail::url_serializer(*d->poster);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_video_element::set_plays_inline(ext::boolean new_plays_inline) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_video_element);
        return d->plays_inline = new_plays_inline;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_video_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_video_element>{isolate}
        .inherit<html_video_element>()
        .ctor<>()
        .property("width", &html_video_element::get_width, &html_video_element::set_width)
        .property("height", &html_video_element::get_height, &html_video_element::set_height)
        .property("videoWidth", &html_video_element::get_video_width)
        .property("videoHeight", &html_video_element::get_video_height)
        .property("poster", &html_video_element::get_poster, &html_video_element::set_poster)
        .property("playsInline", &html_video_element::get_plays_inline, &html_video_element::set_plays_inline)
        .auto_wrap_objects();

    return std::move(conversion);
}
