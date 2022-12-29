module;
#include "ext/macros/macros.hpp"


export module apis.file_api.file_reader_sync_private;
import apis.dom_object_private;


DEFINE_PRIVATE_CLASS(file_api, file_reader_sync)
        : virtual dom_object_private
{
    MAKE_QIMPL(file_reader_sync);
};
