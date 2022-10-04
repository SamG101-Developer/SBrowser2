#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_BLOB_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_BLOB_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include "ext/string.hpp"


DEFINE_PRIVATE_CLASS(file_api, blob) : virtual dom_object_private
{
    ext::string snapshot_state;
    ext::string byte_sequence;
    ext::string type;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_BLOB_PRIVATE_HPP
