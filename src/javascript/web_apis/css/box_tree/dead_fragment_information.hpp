#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_BOX_TREE_DEAD_FRAGMENT_INFORMATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_BOX_TREE_DEAD_FRAGMENT_INFORMATION_HPP

#include "dom_object.hpp"
namespace css::box_tree {class dead_fragment_information;}

#include "ext/boolean.ixx"


class css::box_tree::dead_fragment_information
        : public virtual dom_object
{
public constructors:
    dead_fragment_information() = default;

private js_properties:
    ext::property<std::unique_ptr<dom::nodes::node>> node;
    ext::property<ext::number<double>> width;
    ext::property<ext::number<double>> height;
    ext::property<ext::number<double>> top;
    ext::property<ext::number<double>> left;
    ext::property<ext::boolean> is_overflowed;

    ext::property<std::unique_ptr<ext::vector<dead_fragment_information*>>> children;
    ext::property<dead_fragment_information*> next_sibling;
    ext::property<dead_fragment_information*> prev_sibling;
    ext::property<dead_fragment_information*> next_in_box;
    ext::property<dead_fragment_information*> prev_in_box;

private cpp_members:
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_BOX_TREE_DEAD_FRAGMENT_INFORMATION_HPP
