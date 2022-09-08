#include "html_video_element.hpp"
#include "html/_typedefs.hpp"


auto html::elements::html_video_element::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<html_video_element>{isolate}
        .ctor<>()
        .var("width", &html_video_element::width, true)
        .var("height", &html_video_element::height, true)
        .var("videoWidth", &html_video_element::width, false)
        .var("videoHeight", &html_video_element::height, false)
        .var("poster", &html_video_element::width, true)
        .var("playsInline", &html_video_element::height, true)
        .auto_wrap_objects();
}
