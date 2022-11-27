#include "media_metadata.hpp"
#include "media_metadata_private.hpp"

#include "dom/detail/observer_internals.hpp"
#include "html/detail/task_internals.hpp"
#include "mediasession/detail/media_session_internals.hpp"


mediasession::media_metadata::media_metadata(detail::media_metadata_init_t&& init)
{
    INIT_PIMPL(media_metadata);

    ACCESS_PIMPL(media_metadata);
    d->title = std::move(init[u"title"].to<decltype(d->title)>());
    d->artist = std::move(init[u"artist"].to<decltype(d->artist)>());
    d->album = std::move(init[u"album"].to<decltype(d->album)>());
    d->artwork_images = detail::convert_artwork(std::move(init[u"artwork"].to<ext::vector<detail::media_image_t>>()));
}


auto mediasession::media_metadata::get_title() const -> ext::string_view
{
    ACCESS_PIMPL(const media_metadata);
    return d->title;
}


auto mediasession::media_metadata::get_artist() const -> ext::string_view
{
    ACCESS_PIMPL(const media_metadata);
    return d->artist;
}


auto mediasession::media_metadata::get_album() const -> ext::string_view
{
    ACCESS_PIMPL(const media_metadata);
    return d->album;
}


auto mediasession::media_metadata::get_artwork() const -> ext::frozen_vector<detail::media_image_t>&
{
    ACCESS_PIMPL(const media_metadata);
    return d->artwork_images;
}


auto mediasession::media_metadata::set_title(ext::string new_title) -> ext::string
{
    ACCESS_PIMPL(media_metadata);
    d->title = std::move(new_title);

    return_if (!d->media_session) d->title;
    dom::detail::queue_task(html::detail::media_session_task_source,
        [d] {if (d->media_session) GO &detail::update_metadata;});

    return d->title;
}


auto mediasession::media_metadata::set_artist(ext::string new_artist) -> ext::string
{
    ACCESS_PIMPL(media_metadata);
    return d->artist = std::move(new_artist);

    return_if (!d->media_session) d->artist;
    dom::detail::queue_task(html::detail::media_session_task_source,
        [d] {if (d->media_session) GO &detail::update_metadata;});

    return d->artist;
}


auto mediasession::media_metadata::set_album(ext::string new_album) -> ext::string
{
    ACCESS_PIMPL(media_metadata);
    // TODO

    return_if (!d->media_session) d->album;
    dom::detail::queue_task(html::detail::media_session_task_source,
        [d] {if (d->media_session) GO &detail::update_metadata;});

    return d->album;
}


auto mediasession::media_metadata::set_artwork(ext::frozen_vector<detail::media_image_t>& new_artwork) -> const ext::frozen_vector<detail::media_image_t>&
{
    ACCESS_PIMPL(media_metadata);
    // TODO

    return_if (!d->media_session) d->artwork_images;
    dom::detail::queue_task(html::detail::media_session_task_source,
        [d] {if (d->media_session) GO &detail::update_metadata;});

    return d->artwork_images;
}

