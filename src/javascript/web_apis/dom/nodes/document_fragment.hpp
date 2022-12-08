#ifndef SBROWSER2_DOCUMENT_FRAGMENT_HPP
#define SBROWSER2_DOCUMENT_FRAGMENT_HPP




namespace dom::nodes {class document_fragment;}
namespace dom::nodes {class document_fragment_private;}

namespace dom::node_ranges {class range;}


class dom::nodes::document_fragment
        : public node
        , public mixins::non_element_parent_node
        , public mixins::parentable_node
{
public friends:
    friend dom::node_ranges::range;

public:
    DOM_CTORS(document_fragment);
    MAKE_PIMPL(document_fragment);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return DOCUMENT_FRAGMENT_NODE;}
    DEFINE_GETTER(node_name, ext::string) override;
    DEFINE_GETTER(node_value, ext::string) override;
    DEFINE_GETTER(text_content, ext::string) override;

    DEFINE_SETTER(node_value, ext::string) override {}
    DEFINE_SETTER(text_content, ext::string) override;
};


#endif //SBROWSER2_DOCUMENT_FRAGMENT_HPP
