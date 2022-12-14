module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"
#include <function2/function2.hpp>


export module apis.web_audio.base_audio_context;
import apis.dom.event_target;

import apis.web_audio.types;

import ext.any;
import ext.array_buffer;
import ext.functional;
import ext.map;
import ext.number;
import ext.promise;
import ext.string;
import ext.tuple;
import ext.vector;

import js.env.module_type;

namespace dom {class dom_exception;}
namespace web_audio {class analyser_node;}
namespace web_audio {class audio_buffer;}
namespace web_audio {class audio_buffer_source_node;}
namespace web_audio {class audio_destination_node;}
namespace web_audio {class audio_listener;}
namespace web_audio {class audio_worklet;}
namespace web_audio {class biquad_filter_node;}
namespace web_audio {class channel_merger_node;}
namespace web_audio {class channel_splitter_node;}
namespace web_audio {class constant_source_node;}
namespace web_audio {class convolver_node;}
namespace web_audio {class delay_node;}
namespace web_audio {class dynamic_compressor_node;}
namespace web_audio {class gain_node;}
namespace web_audio {class iir_filter_node;}
namespace web_audio {class oscillator_node;}
namespace web_audio {class panner_node;}
namespace web_audio {class periodic_wave;}
namespace web_audio {class script_processor_node;}
namespace web_audio {class stereo_panner_node;}
namespace web_audio {class wave_shaper_node;}


DEFINE_PUBLIC_CLASS(web_audio, base_audio_context)
        : public dom::event_target
{
public typedefs:
    using decode_error_callback_t = ext::function<void(dom::dom_exception&& error)>;
    using decode_success_callback_t = ext::function<void(audio_buffer* decoded_data)>;
    using periodic_wave_constaints_t = ext::map<ext::string, ext::any>;

public constructors:
    DOM_CTORS(base_audio_context);
    MAKE_PIMPL(base_audio_context);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto create_analyser() -> std::unique_ptr<analyser_node>;
    auto create_biquad_filter() -> std::unique_ptr<biquad_filter_node>;
    auto create_audio_buffer(ext::number<ulong> number_of_channels, ext::number<ulong> length, ext::number<float> sample_rate) -> std::unique_ptr<audio_buffer>;
    auto create_buffer_source() -> std::unique_ptr<audio_buffer_source_node>;
    auto create_channel_merger(ext::number<ulong> number_of_outputs = 6) -> std::unique_ptr<channel_merger_node>;
    auto create_channel_splitter(ext::number<ulong> number_of_outputs = 6) -> std::unique_ptr<channel_splitter_node>;
    auto create_constant_source() -> std::unique_ptr<constant_source_node>;
    auto create_convolver() -> std::unique_ptr<convolver_node>;
    auto create_delay_node(ext::number<double> delay_time = 1.0) -> std::unique_ptr<delay_node>;
    auto create_dynamic_compressor() -> std::unique_ptr<dynamic_compressor_node>;
    auto create_gain() -> std::unique_ptr<gain_node>;
    auto create_iir_filter_node(ext::vector<ext::number<double>>&& feed_forward, ext::vector<ext::number<double>>&& feedback) -> std::unique_ptr<iir_filter_node>;
    auto create_oscillator() -> std::unique_ptr<oscillator_node>;
    auto create_panner() -> std::unique_ptr<panner_node>;
    auto create_periodic_wave(ext::vector<ext::number<float>> real, ext::vector<ext::number<float>> imag, periodic_wave_constaints_t&& constraints = {}) -> std::unique_ptr<periodic_wave>;
    auto create_script_processor_node(ext::number<ulong> buffer_size = 0, ext::number<ulong> number_of_input_channels = 2, ext::number<ulong> number_of_output_channels = 2) -> std::unique_ptr<script_processor_node>;
    auto create_stereo_panner() -> std::unique_ptr<stereo_panner_node>;
    auto create_wave_shaper() -> std::unique_ptr<wave_shaper_node>;

    auto decode_audio_data(ext::array_buffer* data, decode_success_callback_t&& success_callback, decode_error_callback_t&& error_callback) -> ext::promise<std::unique_ptr<audio_buffer>>;

public js_properties:
    DEFINE_GETTER(destination, audio_destination_node*);
    DEFINE_GETTER(sample_rate, ext::number<float>);
    DEFINE_GETTER(current_time, ext::number<double>);
    DEFINE_GETTER(listener, audio_listener*);
    DEFINE_GETTER(state, detail::audio_context_state_t);
    DEFINE_GETTER(audio_worklet, audio_worklet*);
};
