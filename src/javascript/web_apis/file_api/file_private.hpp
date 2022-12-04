#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_FILE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_FILE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "file_api/blob_private.hpp"





DEFINE_PRIVATE_CLASS(file_api, file)
        : blob_private
{
    MAKE_QIMPL(file);

    ext::string name;
    ext::number<longlong> last_modified;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_FILE_PRIVATE_HPP
