module;
#include "ext/macros.hpp"


export module apis.dom.static_range;
import apis.dom.abstract_range;


DEFINE_PUBLIC_CLASS(dom, static_range) final
        : public dom::abstract_range
{
public typedefs:
    using static_range_init_t = ext::map<ext::string, ext::any>;

public constructors:
    static_range(static_range_init_t&& init = {});
    MAKE_PIMPL(static_range);
    MAKE_V8_AVAILABLE(WINDOW);
};
