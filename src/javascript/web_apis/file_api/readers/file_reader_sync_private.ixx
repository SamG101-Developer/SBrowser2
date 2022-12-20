module;
#include "ext/macros/pimpl.hpp"


export module apis.file_api.file_reader_sync_private;
import apis._.dom_object_private;


DEFINE_PRIVATE_CLASS(file_api, file_reader_sync)
        : virtual dom_object_private
{
    MAKE_QIMPL(file_reader_sync);
};
