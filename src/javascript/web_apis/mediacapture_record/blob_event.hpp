#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_BLOB_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_BLOB_EVENT_HPP

#include "dom/events/event.hpp"
namespace mediacapture::record {class blob_event;}

#include USE_INNER_TYPES(hr_time)
namespace file_api {class blob;}


class mediacapture::record::blob_event
        : public dom::events::event
{
public constructors:
    blob_event() = default;
    blob_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<std::unique_ptr<file_api::blob>> blob;
    ext::property<hr_time::dom_high_res_time_stamp> timecode;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_BLOB_EVENT_HPP
