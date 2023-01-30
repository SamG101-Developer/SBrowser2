module;
#include "ext/macros.hpp"
#include <tuplet/tuple.hpp>


export module apis.dom.range:p;
import apis.dom.abstract_range;
import apis.dom.types;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, range) final
        : abstract_range_private
{
public:
    MAKE_QIMPL(range);
    friend class dom::character_data_private;
};
