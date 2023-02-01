module;
#include "ext/macros.hpp"

export module apis.dom.character_data;
import apis.dom.node;
import apis.dom.mixins.child_node;
import apis.dom.mixins.non_document_type_child_node;


DEFINE_PUBLIC_CLASS(dom, character_data)
        : public dom::node
        , public dom::mixins::child_node
        , public dom::mixins::non_document_type_child_node
{
public constructors:
    character_data();
    MAKE_PIMPL(character_data);
    MAKE_V8_AVAILABLE(WINDOW);

private js_methods:
    _EXT_NODISCARD auto substring_data(ext::number<ulong> offset, ext::number<ulong> count) const -> ext::string;
    auto append_data(ext::string&& new_data) -> ext::string;
    auto insert_data(ext::number<ulong> offset, ext::string&& new_data) -> ext::string;
    auto delete_data(ext::number<ulong> offset, ext::number<ulong> count) -> ext::string;
    auto replace_data(ext::number<ulong> offset, ext::number<ulong> count, ext::string&& new_data) -> ext::string;

private js_properties:
    DEFINE_GETTER(node_name, ext::string) override {return u"";};
    DEFINE_GETTER(node_value, ext::string) override;
    DEFINE_GETTER(text_content, ext::string) override;
    DEFINE_GETTER(data, ext::string);
    DEFINE_GETTER(length, ext::number<ulong>);

    DEFINE_SETTER(node_value, ext::string) override;
    DEFINE_SETTER(text_content, ext::string) override;
    DEFINE_SETTER(data, ext::string);
};
