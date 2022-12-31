module;
#include "ext/macros.hpp"


export module apis.dom.abstract_range:p;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, abstract_range)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(abstract_range);

public:
    std::unique_ptr<detail::boundary_point_t> start;
    std::unique_ptr<detail::boundary_point_t> end;

public:
    auto is_range_collapsed() const -> ext::boolean;
};
