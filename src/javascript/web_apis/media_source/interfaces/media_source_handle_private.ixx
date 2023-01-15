module;
#include "ext/macros.hpp"


export module apis.media_source.media_source_handle:p;
import apis.dom_object;
import apis.media_source.media_source_handle;


DEFINE_PRIVATE_CLASS(media_source, media_source_handle) : virtual dom_object_private
{
public:
    MAKE_QIMPL(media_source_handle);

public:
    ext::boolean has_ever_been_assigned_as_srcobject;
    ext::boolean detached;
    std::observer_ptr<media_source> media_source;
};
