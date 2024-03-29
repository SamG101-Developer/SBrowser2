module;
#include "ext/macros.hpp"


export module apis.filesystem.file_system_handle;
import apis.dom_object;

IMPORT_ALL_TYPES(filesystem);


DEFINE_PUBLIC_CLASS(filesystem, file_system_handle)
        : virtual public dom_object
{
public constructors:
    file_system_handle();
    MAKE_PIMPL(file_system_handle);
    MAKE_V8_AVAILABLE(WINDOW | WORKER | SECURE);
    MAKE_SERIALIZABLE;

private js_methods:
    auto is_same_entry(file_system_handle* other) const -> ext::promise<ext::boolean>;

private js_properties:
    DEFINE_GETTER(kind, detail::file_system_handle_kind_t);
    DEFINE_GETTER(name, ext::string_view);
};
