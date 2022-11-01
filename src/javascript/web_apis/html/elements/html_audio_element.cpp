#include "html_audio_element.hpp"
#include "html_audio_element_private.hpp"


html::elements::html_audio_element::html_audio_element()
{
    INIT_PIMPL(html_audio_element);
    HTML_CONSTRUCTOR
}


auto html::elements::html_audio_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_audio_element>{isolate}
        .inherit<html_media_element>()
        .ctor<>()
        .auto_wrap_objects();

    return std::move(conversion);
}
