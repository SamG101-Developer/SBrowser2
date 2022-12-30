module;
#include "ext/macros.hpp"


export module apis.dom.character_data:p;
import apis.dom.node;
import apis.dom.mixins.child_node;
import apis.dom.mixins.non_document_type_child_node;


DEFINE_PRIVATE_CLASS(dom, character_data)
        : dom::mixins::node_private
        , dom::mixins::child_node_private
        , dom::mixins::non_document_type_child_node_private
{
public:
    MAKE_QIMPL(character_data);

public:
    ext::string data;

public:
    auto replace_data(ext::number<ulong> offset, ext::number<ulong> count, ext::string&& new_data) -> void;
    auto substring_data(ext::number<ulong> offset, ext::number<ulong> count) const -> ext::string;
    auto split(ext::number<ulong> offset) -> std::unique_ptr<text>;
};
