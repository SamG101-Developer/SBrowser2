#pragma once
#ifndef SBROWSER2_HTML_MEDIA_ELEMENT_HPP
#define SBROWSER2_HTML_MEDIA_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_media_element;}

namespace html::basic_media {class media_error;}
namespace mediacapture::main {class media_stream;}


class html::elements::html_media_element
        : public html_element
{
public js_methods:
    /* MEDIACAPTURE-FROMELEMENT */
    auto capture_stream() -> mediacapture::main::media_stream;

public cpp_properties:
    ext::property<basic_media::media_error*> error;
    ext::property<ext::string> src;
    ext::property<ext::string> src_object;
};


#endif //SBROWSER2_HTML_MEDIA_ELEMENT_HPP
