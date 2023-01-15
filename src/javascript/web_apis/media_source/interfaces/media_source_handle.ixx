module;
#include "ext/macros.hpp"


export module apis.media_source.media_source_handle;
import apis.dom_object;


DEFINE_PUBLIC_CLASS(media_source, media_source_handle) final
        : public virtual dom_object
{
public constructors:
    media_source_handle();
    MAKE_PIMPL(media_source_handle);
    MAKE_TRANSFERABLE(media_source_handle);
    MAKE_V8_AVAILABLE(WINDOW | DEDICATED_WORKER);
};
