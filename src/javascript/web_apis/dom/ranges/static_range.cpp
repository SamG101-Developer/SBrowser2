#include "static_range.hpp"

#include "ext/casting.hpp"

#include INCLUDE_INNER_TYPES(dom)

#include "dom/detail/exception_internals.hpp"
#include "dom/detail/range_internals.hpp"
#include "dom/nodes/attr.hpp"
#include "dom/nodes/document_type.hpp"


dom::node_ranges::static_range::static_range(
        detail::static_range_init_t&& init)
{
    INIT_PIMPL(static_range);
    ACCESS_PIMPL(static_range);

    using enum detail::dom_exception_error_t;

    d->start->node = init.try_emplace("startContainer", nullptr).first->second.to<nodes::node*>();
    d->end->node = init.try_emplace("endContainer", nullptr).first->second.to<nodes::node*>();
    d->start->offset = init.try_emplace("startOffset", 0).first->second.to<ext::number<ulong>>();
    d->end->offset = init.try_emplace("endOffset", 0).first->second.to<ext::number<ulong>>();

    detail::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [d] {return dom_multi_cast<nodes::document_type*, nodes::attr*>(d->start->node);},
            "Start container can not be a DocumentType or Attribute node");

    detail::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [d] {return dom_multi_cast<nodes::document_type*, nodes::attr*>(d->end->node);},
            "End container can not be a DocumentType or Attribute node");
}


auto dom::node_ranges::static_range::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<static_range>{isolate}
        .inherit<abstract_range>()
        .ctor<detail::static_range_init_t>()
        .auto_wrap_objects();

    return std::move(conversion);
}
