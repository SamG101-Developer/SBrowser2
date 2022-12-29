module;
#include "ext/macros/pimpl.hpp"


export module apis.html.broadcast_channel_private;
import apis.dom.event_target_private;

import ext.boolean;
import ext.string;


DEFINE_PRIVATE_CLASS(html, broadcast_channel)
        : dom::event_target_private
{
public:
    MAKE_QIMPL(broadcast_channel);

public:
    auto is_eligible_for_messaging() const -> ext::boolean;

public:
    ext::string channel_name;
    ext::boolean closed_flag;
};
