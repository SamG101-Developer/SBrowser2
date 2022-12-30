module;
#include "ext/macros.hpp"


export module apis.clipboard.clipboard_event:p;
import apis.dom.event;

namespace html {class data_transfer;}


DEFINE_PRIVATE_CLASS(clipboard, clipboard_event)
        : dom::event_private
{
public:
    MAKE_QIMPL(clipboard_event);

public:
    std::unique_ptr<html::data_transfer> clipboard_data;
};
