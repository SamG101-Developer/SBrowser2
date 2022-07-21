#include "html_source_element.hpp"


html::elements::html_source_element::html_source_element()
{
    m_dom_behaviour.insertion_steps = []
    {
        /* TODO : HTMLMediaElement parent handling
         * TODO : HTMLPictureElement stuff */
    };

    m_dom_behaviour.remove_steps = [](dom::nodes::node* old_parent)
    {
        /* TODO : HTMLPictureElement stuff */
    };

    HTML_CONSTRUCTOR
}


auto html::elements::html_source_element::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<html_source_element>{isolate}
            .ctor<>()
            .inherit<html_element>()
            .var("src", &html_source_element::src, false)
            .var("type", &html_source_element::type, false)
            .var("srcset", &html_source_element::srcset, false)
            .var("sizes", &html_source_element::sizes, false)
            .var("media", &html_source_element::media, false)
            .var("width", &html_source_element::width, false)
            .var("height", &html_source_element::height, false)
            .auto_wrap_objects();
}

