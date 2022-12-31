module;
#include "ext/macros.hpp"


export module apis.file_api.file:p;
import apis.file_api.blob;


DEFINE_PRIVATE_CLASS(file_api, file)
        : blob_private
{
    MAKE_QIMPL(file);

    ext::string name;
    ext::number<longlong> last_modified;
};
