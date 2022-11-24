#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_HANDLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_HANDLE_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace filesystem {class file_system_handle;}
namespace filesystem {class file_system_handle_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(filesystem)
#include INCLUDE_CONCEPTS(html)
#include "ext/promise.hpp"


class filesystem::file_system_handle
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


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_HANDLE_HPP
