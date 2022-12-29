module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.character_data_private;
import apis.dom.node_private;
import apis.dom.mixins.child_node_private;
import apis.dom.mixins.non_document_type_child_node_private;

import apis.dom.types;
import ext.core;


DEFINE_PRIVATE_CLASS(dom, character_data)
        : dom::node_private
        , dom::child_node_private
        , dom::non_document_type_child_node_private
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
