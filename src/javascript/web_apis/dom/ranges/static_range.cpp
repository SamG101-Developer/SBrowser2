#include "static_range.hpp"

#include <ext/casting.hpp>

#include <web_apis/dom/detail/exception_internals.hpp>
#include <web_apis/dom/nodes/attr.hpp>
#include <web_apis/dom/nodes/document_type.hpp>


dom::node_ranges::static_range::static_range(
        ext::string_any_map_view init)
{
    start_container = init.at("startContainer").value_to_or<nodes::node*>(nullptr);
    end_container   = init.at("startContainer").value_to_or<nodes::node*>(nullptr);
    start_offset    = init.at("startOffset").value_to_or<ext::number<ulong>>(0);
    end_offset      = init.at("endOffset").value_to_or<ext::number<ulong>>(0);

    detail::exception_internals::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [this] {return ext::multi_cast<nodes::document_type*, nodes::attr*>(start_container());},
            "Start container can not be a DocumentType or Attribute node");

    detail::exception_internals::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [this] {return ext::multi_cast<nodes::document_type*, nodes::attr*>(end_container());},
            "End container can not be a DocumentType or Attribute node");
}
