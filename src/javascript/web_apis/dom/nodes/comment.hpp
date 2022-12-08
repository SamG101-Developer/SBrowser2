#ifndef SBROWSER2_COMMENT_HPP
#define SBROWSER2_COMMENT_HPP


namespace dom::nodes {class comment;}
namespace dom::nodes {class comment_private;}


class dom::nodes::comment final
        : public character_data
{
public constructors:
    explicit comment(ext::string&& new_data = "");
    MAKE_PIMPL(comment);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return COMMENT_NODE;}
    DEFINE_GETTER(node_name, ext::string) override;
};


#endif //SBROWSER2_COMMENT_HPP
