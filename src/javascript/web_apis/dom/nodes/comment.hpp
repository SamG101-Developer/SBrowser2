#ifndef SBROWSER2_COMMENT_HPP
#define SBROWSER2_COMMENT_HPP

#include "dom/nodes/character_data.hpp"
namespace dom::nodes {class comment;}


#include "dom/nodes/comment_private.hpp"


class dom::nodes::comment final
        : public character_data
{
public constructors:
    explicit comment(ext::string&& new_data = "");
    MAKE_PIMPL(comment);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return COMMENT_NODE;}
    DEFINE_GETTER(node_name, ext::string) override {return "#comment";}
};


#endif //SBROWSER2_COMMENT_HPP
