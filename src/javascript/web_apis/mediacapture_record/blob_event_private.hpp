#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_BLOB_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_BLOB_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include "ext/memory.ixx"
namespace file_api {class blob;}


DEFINE_PRIVATE_CLASS(mediacapture::record, blob_event) : dom::events::event_private
{
    std::observer_ptr<file_api::blob> data;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_RECORD_BLOB_EVENT_PRIVATE_HPP
