module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/other.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.filesystem.file_system_handle;
import apis.dom_object;

import apis.filesystem.types;
import ext.core;
import ext.js;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(filesystem, file_system_handle)
        : virtual public dom_object
{
public constructors:
    file_system_handle();
    MAKE_PIMPL(file_system_handle);
    MAKE_V8_AVAILABLE(WINDOW | WORKER | SECURE);
    MAKE_SERIALIZABLE;

public js_methods:
    auto is_same_entry(file_system_handle* other) const -> ext::promise<ext::boolean>;

public js_properties:
    DEFINE_GETTER(kind, detail::file_system_handle_kind_t);
    DEFINE_GETTER(name, ext::string_view);
};
