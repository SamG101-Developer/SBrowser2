#ifndef SBROWSER2_COMMENT_HPP
#define SBROWSER2_COMMENT_HPP

#include "dom/nodes/character_data.hpp"
namespace dom::nodes {class comment;}


class dom::nodes::comment final
        : public character_data
{
public constructors:
    explicit comment(ext::string&& new_data = "");

public cpp_members:
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(node_type) override {return COMMENT_NODE;}
    DEFINE_CUSTOM_GETTER(node_name) override {return "#comment";}
};


#endif //SBROWSER2_COMMENT_HPP
