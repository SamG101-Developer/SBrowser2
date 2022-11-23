#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_FILE_READER_SYNC_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_FILE_READER_SYNC_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS(file_api, file_reader_sync)
        : virtual dom_object_private
{
    MAKE_QIMPL(file_reader_sync);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_FILE_READER_SYNC_PRIVATE_HPP
