#include "static_range.hpp"

#include "ext/casting.hpp"

#include "dom/detail/exception_internals.hpp"
#include "dom/detail/range_internals.hpp"
#include "dom/nodes/attr.hpp"
#include "dom/nodes/document_type.hpp"


dom::node_ranges::static_range::static_range(
        detail::static_range_init_t&& init)
        : INIT_PIMPL
{
    abstract_range::d_ptr->start->node = init.try_emplace("startContainer", nullptr).first->second.to<nodes::node*>();
    abstract_range::d_ptr->end->node = init.try_emplace("endContainer", nullptr).first->second.to<nodes::node*>();
    abstract_range::d_ptr->start->offset = init.try_emplace("startOffset", 0).first->second.to<ext::number<ulong>>();
    abstract_range::d_ptr->end->offset = init.try_emplace("endOffset", 0).first->second.to<ext::number<ulong>>();

    detail::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [this] {return ext::multi_cast<nodes::document_type*, nodes::attr*>(abstract_range::d_ptr->start->node);},
            "Start container can not be a DocumentType or Attribute node");

    detail::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [this] {return ext::multi_cast<nodes::document_type*, nodes::attr*>(abstract_range::d_ptr->end->node);},
            "End container can not be a DocumentType or Attribute node");
}
