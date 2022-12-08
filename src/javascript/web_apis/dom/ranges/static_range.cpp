#include "static_range.hpp"
#include "static_range_private.hpp"










dom::node_ranges::static_range::static_range(detail::static_range_init_t&& init)
{
    INIT_PIMPL(static_range);
    ACCESS_PIMPL(static_range);

    using enum detail::dom_exception_error_t;

    d->start->node = init[u"startContainer"].to<decltype(d->start->node)>();
    d->end->node = init[u"endContainer"].to<decltype(d->end->node)>();
    d->start->offset = init[u"startOffset"].to<decltype(d->start->offset)>();
    d->end->offset = init[u"endOffset"].to<decltype(d->end->offset)>();

    detail::throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [d] {return dom_multi_cast<nodes::document_type*, nodes::attr*>(d->start->node.get());},
            u8"Start container can not be a DocumentType or Attribute node");

    detail::throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [d] {return dom_multi_cast<nodes::document_type*, nodes::attr*>(d->end->node.get());},
            u8"End container can not be a DocumentType or Attribute node");
}


auto dom::node_ranges::static_range::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<abstract_range>()
        .ctor<detail::static_range_init_t>()
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
