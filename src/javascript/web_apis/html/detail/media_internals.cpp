#include "media_internals.hpp"

#include "html/elements/html_media_element.hpp"
#include "html/elements/html_video_element.hpp"


auto html::detail::media_element_load_algorithm(
        elements::html_media_element* element)
        -> void
{
    /* MEDIA_PLAYBACK_QUALITY*/
    if (decltype(auto) video_element = dynamic_cast<elements::html_video_element*>(element))
    {
        video_element->m_total_video_frame_count = 0;
        video_element->m_dropped_video_frame_count = 0;
    }
}
