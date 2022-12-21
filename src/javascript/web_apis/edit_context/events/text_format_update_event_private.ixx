module;
#include "ext/macros/pimpl.hpp"


export module apis.edit_context.text_format_update_event_private;
import apis.dom.event_private;

import ext.core;
namespace edit_context {class text_format;}


DEFINE_PRIVATE_CLASS(edit_context, text_format_update_event)
        : dom::event_private
{
public:
    MAKE_QIMPL(text_format_update_event);

public:
    ext::vector<std::unique_ptr<text_format>> text_formats;
};
