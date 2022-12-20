module;
#include "ext/macros/pimpl.hpp"


export module apis.clipboard.clipboard_item_private;
import apis._.dom_object_private;


DEFINE_PRIVATE_CLASS(clipboard, clipboard_item)
        : dom_object_private
{
public:
    MAKE_QIMPL(clipboard_item);
};
