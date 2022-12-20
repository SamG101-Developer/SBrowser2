module;
#include "ext/macros/pimpl.hpp"


export module apis.file_api.blob_private;
import apis._.dom_object_private;

import ext.string;


DEFINE_PRIVATE_CLASS(file_api, blob)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(blob);

public:
    ext::string snapshot_state;
    ext::string byte_sequence;
    ext::string type;
};
