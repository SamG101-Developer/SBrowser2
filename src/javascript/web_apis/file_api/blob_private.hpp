#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_BLOB_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_BLOB_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"




DEFINE_PRIVATE_CLASS(file_api, blob)
        : virtual dom_object_private
{
    MAKE_QIMPL(blob);

    ext::string snapshot_state;
    ext::string byte_sequence;
    ext::string type;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_BLOB_PRIVATE_HPP
