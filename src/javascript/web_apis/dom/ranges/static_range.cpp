#include "static_range.hpp"

#include "ext/casting.hpp"

#include "dom/detail/exception_internals.hpp"
#include "dom/nodes/attr.hpp"
#include "dom/nodes/document_type.hpp"


dom::node_ranges::static_range::static_range(
        ext::map<ext::string, ext::any>&& init)
{
    start_container = init.try_emplace("startContainer", nullptr).first->second.to<nodes::node*>();
    end_container   = init.try_emplace("endContainer", nullptr).first->second.to<nodes::node*>();
    start_offset    = init.try_emplace("startOffset", 0).first->second.to<ext::number<ulong>>();
    end_offset      = init.try_emplace("endOffset", 0).first->second.to<ext::number<ulong>>();

    detail::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [this] {return ext::multi_cast<nodes::document_type*, nodes::attr*>(start_container());},
            "Start container can not be a DocumentType or Attribute node");

    detail::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [this] {return ext::multi_cast<nodes::document_type*, nodes::attr*>(end_container());},
            "End container can not be a DocumentType or Attribute node");
}
