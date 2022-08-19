#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HANDLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HANDLE_HPP

#include "dom_object.hpp"
#include "html/mixins/transferable.hpp"
namespace media::source {class media_source_handle;}

class media::source::media_source_handle
        : public virtual dom_object
        , public html::mixins::transferable
{
public constructors:
    DOM_CTORS(media_source_handle);
    media_source_handle() = default;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HANDLE_HPP
