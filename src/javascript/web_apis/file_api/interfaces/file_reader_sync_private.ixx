module;
#include "ext/macros.hpp"


export module apis.file_api.file_reader_sync:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(file_api, file_reader_sync)
        : virtual dom_object_private
{
    MAKE_QIMPL(file_reader_sync);
};
