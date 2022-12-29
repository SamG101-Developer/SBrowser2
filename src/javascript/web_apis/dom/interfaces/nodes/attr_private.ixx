module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.attr_private;
import apis.dom.node_private;

import apis.dom.types;
import ext.core;


DEFINE_PRIVATE_CLASS(dom, attr)
        : node_private
{
public:
    MAKE_QIMPL(attr);

public:
    ext::string namespace_;
    ext::string namespace_prefix;
    ext::string local_name;
    ext::string value;
    std::observer_ptr<element> element;

public:
    auto qualified_name() const -> ext::string;
    auto handle_attributes_changes(attr* attribute, class element* owner_element, ext::string_view old_value, ext::string_view new_value) -> void;
    auto set_existing_attribute_value(ext::string&& value) -> void;
};
