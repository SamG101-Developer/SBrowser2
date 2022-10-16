#include "text_track.hpp"
#include "text_track_private.hpp"

#include "html/basic_media/abstract_track.hpp"
#include "html/basic_media/text_track_cue.hpp"
#include "html/basic_media/text_track_cue_private.hpp"


auto html::basic_media::text_track::get_in_band_metadata_track_dispatch_type() const -> ext::string_view
{
    ACCESS_PIMPL(const text_track);
    return d->in_band_metadata_track_dispatch_type;
}


auto html::basic_media::text_track::get_mode() const -> detail::track_mode_t
{
    ACCESS_PIMPL(const text_track);
    return d->mode;
}


auto html::basic_media::text_track::get_cues() const -> ranges::any_helpful_view<text_track_cue*>
{
    ACCESS_PIMPL(const text_track);
    return d->text_track_cues
            | ranges::views::transform(&std::unique_ptr<text_track_cue>::get)
            | ranges::views::filter([this](text_track_cue* cue) {return cue->d_func()->end_time >= detail::ealiest_possible_position_when_script_started(this);});
}


auto html::basic_media::text_track::get_active_cues() const -> ranges::any_helpful_view<text_track_cue*>
{
    ACCESS_PIMPL(const text_track);
    return d->text_track_cues
            | ranges::views::transform(&std::unique_ptr<text_track_cue>::get)
            | ranges::views::filter([](text_track_cue* cue) {return detail::active_flag_set_when_scriptstarted(cue);});
}


auto html::basic_media::text_track::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<text_track>{isolate}
        .inherit<abstract_track>()
        .property("inBandMetadataTrackDispatchType", &text_track::get_in_band_metadata_track_dispatch_type)
        .property("mode", &text_track::get_mode)
        .property("cues", &text_track::get_cues)
        .property("activeCues", &text_track::get_active_cues)
        .auto_wrap_objects();

    return std::move(conversion);
}
