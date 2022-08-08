#pragma once
#ifndef SBROWSER2_HTML_MEDIA_ELEMENT_HPP
#define SBROWSER2_HTML_MEDIA_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_media_element;}
namespace html::media {class media_error;}


class html::elements::html_media_element
        : public html_element
{
public cpp_properties:
    ext::property<media::media_error*> error;
    ext::property<ext::string> src;
    ext::property<ext::string> src_object;
};


#endif //SBROWSER2_HTML_MEDIA_ELEMENT_HPP
