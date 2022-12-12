module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.abstract_range_private;
import apis._.dom_object_private;
import apis.dom.types;


DEFINE_PRIVATE_CLASS(dom, abstract_range)
        : virtual dom_object_private
{
    MAKE_QIMPL(abstract_range);
    std::unique_ptr<detail::boundary_point_t> start;
    std::unique_ptr<detail::boundary_point_t> end;

    auto is_range_collapsed() const -> ext::boolean;
};
