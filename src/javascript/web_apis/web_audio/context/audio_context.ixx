module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"
#include <swl/variant.hpp>


export module apis.web_audio.audio_context;
import apis.web_audio.base_audio_context;

import ext.any;
import ext.tuple;
import ext.map;
import ext.number;
import ext.promise;
import ext.string;
import ext.variant;

import js.env.module_type;

namespace web_audio {class audio_render_capacity;}
namespace web_audio {class audio_sink_info;}
namespace web_audio {class media_element_audio_source_node;}
namespace web_audio {class media_stream_audio_source_node;}
namespace web_audio {class media_stream_track_audio_source_node;}
namespace web_audio {class media_stream_audio_destination_node;}
namespace html {class html_media_element;}
namespace media_capture {class media_stream;}
namespace media_capture {class media_stream_track;}


DEFINE_PUBLIC_CLASS(web_audio, audio_context)
        : public web_audio::base_audio_context
{
public typedefs:
    using audio_context_options_t = ext::map<ext::string, ext::any>;
    using audio_timestamp_t = ext::map<ext::string, ext::any>;
    using audio_sink_options_t = ext::map<ext::string, ext::any>;

public constructors:
    audio_context(audio_context_options_t&& options = {});
    DOM_CTORS(audio_context);
    MAKE_PIMPL(audio_context);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto get_output_timestamp() -> audio_timestamp_t;
    auto resume() -> ext::promise<void>;
    auto suspend() -> ext::promise<void>;
    auto close() -> ext::promise<void>;
    auto set_sink_id(ext::string&& sink_id) -> ext::promise<void>;
    auto set_sink_id(audio_sink_options_t&& sink_id) -> ext::promise<void>;

    auto create_media_element_source(html::html_media_element* media_element) -> std::unique_ptr<media_element_audio_source_node>;
    auto create_media_stream_source(media_capture::media_stream* media_stream) -> std::unique_ptr<media_stream_audio_source_node>;
    auto create_media_stream_track_source(media_capture::media_stream* media_stream_track) -> std::unique_ptr<media_stream_track_audio_source_node>;
    auto create_media_stream_destination() -> std::unique_ptr<media_stream_audio_destination_node>;

public js_properties:
    DEFINE_GETTER(base_latency, ext::number<double>);
    DEFINE_GETTER(output_latency, ext::number<double>);
    DEFINE_GETTER(sink_id, ext::variant<ext::string, audio_sink_info*>);
    DEFINE_GETTER(render_capacity, audio_render_capacity*);
};
