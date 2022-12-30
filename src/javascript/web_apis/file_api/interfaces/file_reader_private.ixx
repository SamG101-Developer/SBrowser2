module;
#include "ext/macros.hpp"


export module apis.file_api.file_reader:p;
import apis.dom.event_target;

import apis.dom.types;
import apis.file_api.types;


DEFINE_PRIVATE_CLASS(file_api, file_reader)
        : dom::event_target_private
{
public:
    MAKE_QIMPL(file_reader);

public:
    detail::state_t state;
    detail::result_t result;
    std::unique_ptr<dom::dom_exception> error;
};
