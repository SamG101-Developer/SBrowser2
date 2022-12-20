module;
#include "ext/macros/pimpl.hpp"


export module apis.file_api.file_private;
import apis.file_api.blob_private;

import ext.number;
import ext.string;


DEFINE_PRIVATE_CLASS(file_api, file)
        : blob_private
{
    MAKE_QIMPL(file);

    ext::string name;
    ext::number<longlong> last_modified;
};
