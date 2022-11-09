#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_BLOB_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_BLOB_EVENT_HPP

#include "dom/events/event.hpp"
namespace mediacapture::record {class blob_event;}
namespace mediacapture::record {class blob_event_private;}

#include INCLUDE_INNER_TYPES(hr_time)
namespace file_api {class blob;}


class mediacapture::record::blob_event
        : public dom::events::event
{
public constructors:
    blob_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(blob_event);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(blob, file_api::blob*);
    DEFINE_GETTER(timecode, hr_time::dom_high_res_time_stamp);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_BLOB_EVENT_HPP
