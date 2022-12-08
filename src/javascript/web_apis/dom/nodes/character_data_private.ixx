module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.character_data_private;
import apis.dom.node_private;
import apis.dom.mixins.child_node_private;
import apis.dom.mixins.non_document_type_child_node_private;
import ext.number;
import ext.string;

namespace dom {class text;}


DEFINE_PRIVATE_CLASS(dom, character_data)
        : dom::node_private
        , dom::mixins::child_node_private
        , dom::mixins::non_document_type_child_node_private
{
    MAKE_QIMPL(character_data);

    ext::string data;

    auto replace_data(ext::number<ulong> offset, ext::number<ulong> count, ext::string&& new_data) -> void;
    auto substring_data(ext::number<ulong> offset, ext::number<ulong> count) -> ext::string;
    auto split(ext::number<ulong> offset) -> std::unique_ptr<text>;
};
