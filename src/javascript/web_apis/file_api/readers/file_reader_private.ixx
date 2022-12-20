module;
#include "ext/macros/pimpl.hpp"


export module apis.file_api.file_reader_private;
import apis.dom.event_target_private;
import apis.file_api.types;

namespace dom {class dom_exception;}


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
