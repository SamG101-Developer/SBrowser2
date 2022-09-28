#include "source_internals.hpp"

#include "ext/threading.hpp"
#include "javascript/environment/realms_2.hpp"

#include "mediacapture_main/media_stream_track.hpp"

#include <range/v3/view/filter.hpp>


auto mediacapture::detail::initialize_underlying_source(
        main::media_stream_track* track,
        media_stream_track_source& source)
        -> void
{
    track->m_source = source;
    track->s_capabilities = {};
    track->s_constraints = {};
    track->s_settings = {};
}


auto mediacapture::detail::tie_track_source_to_context(
        media_stream_track_source& source)
        -> void
{
    // get the relevant JavaScript realm of the source, and extract the set of sources in the media_stream_track_sources
    // slot of the global object
    JS_REALM_GET_RELEVANT(source)
    auto sources = javascript::environment::realms::get<ext::set<media_stream_track_source>*>(
            source_relevant_global_object, "[[media_stream_track_sources]]");

    // insert the source into the sources set - this is what ties the source back to the context; it is bound into the
    // slot in the global object, which is unique to a JavaScript context
    sources->insert(source);
}


auto mediacapture::detail::stop_all_sources(
        v8::Local<v8::Object> global_object)
        -> void
{
    // extract the set of sources in the media_stream_track_sources slot of the 'global_object'
    auto sources = javascript::environment::realms::get<ext::set<media_stream_track_source>*>(
            global_object, "[[media_stream_track_sources]]");

    // the filter checks if the relevant JavaScript realm's global object is the global object that was passed into this
    // method - global objects that match mean that the corresponding source will be kept and therefore stopped in the
    // following loop
    auto filter =
            [global_object](main::media_stream_track* track)
            {JS_REALM_GET_RELEVANT(track) return track_relevant_global_object == global_object;};

    // iterate over each source in the filtered 'sources' list and top each one individually
    auto loop =
            [filter = std::move(filter), sources = std::move(sources)]
            (int, int){for (auto* source: sources | ranges::views::filter(std::move(filter))) /* TODO : stop the source */ ;};

    ext::thread_pool pool{5};
    pool.parallelize_loop(sources->size(), loop).wait();
}



