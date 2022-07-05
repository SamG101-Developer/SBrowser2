#pragma once
#ifndef SBROWSER2_STATIC_RANGE_HPP
#define SBROWSER2_STATIC_RANGE_HPP

#include <web_apis/dom/ranges/abstract_range.hpp>
namespace dom::node_ranges {class static_range;}

#include <ext/map.hpp>


class dom::node_ranges::static_range
        : public abstract_range
{
public constructors:
    static_range(ext::string_any_map_view init);

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_STATIC_RANGE_HPP
