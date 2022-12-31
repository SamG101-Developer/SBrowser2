module;
#include "ext/macros.hpp"


export module apis.file_api.blob:p;
import apis.dom_object;


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
