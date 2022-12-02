#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TRACK_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TRACK_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"

#include "ext/memory.ixx"
#include INCLUDE_INNER_TYPES(html)
namespace html::basic_media {class text_track;}


DEFINE_PRIVATE_CLASS(html::elements, html_track_element) : html::elements::html_element_private
{
    detail::track_element_kind_t kind;
    ext::string src;
    ext::string srclang;
    ext::string label;
    ext::boolean default_;
    ext::number<ushort> ready_state;
    std::observer_ptr<basic_media::text_track> track;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TRACK_ELEMENT_PRIVATE_HPP
