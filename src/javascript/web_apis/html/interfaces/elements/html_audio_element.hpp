#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_AUDIO_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_AUDIO_ELEMENT_HPP

#include "html/elements/html_media_element.hpp"
namespace html::elements {class html_audio_element;}
namespace html::elements {class html_audio_element_private;}


class html::elements::html_audio_element
        : public html::elements::html_media_element
{
public constructors:
    DOM_CTORS(html_audio_element);
    MAKE_PIMPL(html_audio_element);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_AUDIO_ELEMENT_HPP
