module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.range_private;
import apis.dom.abstract_range_private;

namespace dom {class character_data_private;}


DEFINE_PRIVATE_CLASS(dom, range) final
        : abstract_range_private
{
public:
    MAKE_QIMPL(range);
    friend class dom::character_data_private;
};
