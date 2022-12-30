module;
#include "ext/macros.hpp"


export module apis.clipboard.clipboard_item:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(clipboard, clipboard_item)
        : dom_object_private
{
public:
    MAKE_QIMPL(clipboard_item);
};
