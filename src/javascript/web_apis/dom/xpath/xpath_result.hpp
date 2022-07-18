#pragma once
#ifndef SBROWSER2_XPATH_RESULT_HPP
#define SBROWSER2_XPATH_RESULT_HPP

#include "dom_object.hpp"
namespace dom::xpath {class xpath_result;}

#include "ext/number.hpp"
#include "ext/optional.hpp"


class dom::xpath::xpath_result
        : public virtual dom_object
{
public js_static_constants:
    constexpr static const ext::number<ushort> ANY_TYPE = 0;
    constexpr static const ext::number<ushort> NUMBER_TYPE = 1;
    constexpr static const ext::number<ushort> STRING_TYPE = 2;
    constexpr static const ext::number<ushort> BOOLEAN_TYPE = 3;
    constexpr static const ext::number<ushort> UNORDERED_NODE_ITERATOR_TYPE = 4;
    constexpr static const ext::number<ushort> ORDERED_NODE_ITERATOR_TYPE = 5;
    constexpr static const ext::number<ushort> UNORDERED_NODE_SNAPSHOT_TYPE = 6;
    constexpr static const ext::number<ushort> ORDERED_NODE_SNAPSHOT_TYPE = 7;
    constexpr static const ext::number<ushort> ANY_UNORDERED_NODE_TYPE = 8;
    constexpr static const ext::number<ushort> FIRST_ORDERED_NODE_TYPE = 9;

public js_methods:
    auto iterate_next() -> nodes::node*;
    auto  snapshot_item(ext::optional<ext::number<ulong>>) -> nodes::node*;

public js_properties:
    ext::property<ext::number<double>> number_value;
    ext::property<ext::string> string_value;
    ext::property<ext::boolean> boolean_value;
    ext::property<std::unique_ptr<nodes::node>> single_node_value;

    ext::property<ext::boolean> invalid_iterator_state;
    ext::property<ext::number<ulong>> snapshot_length;
    ext::property<ext::number<ushort>> result_type;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_XPATH_RESULT_HPP
