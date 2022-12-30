module apis.web_audio.audio_param:p;

import ext.number;


web_audio::audio_param_private::audio_param_private()
{
    default_value = 0;
    min_value = ext::num<float>::min();
    max_value = ext::num<float>::max();
    value = default_value;
    automation_rate = detail::automation_rate_t::A_RATE;
}
