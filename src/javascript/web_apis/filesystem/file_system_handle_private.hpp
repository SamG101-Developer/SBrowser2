#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_HANDLE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_HANDLE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(filesystem)


DEFINE_PRIVATE_CLASS(filesystem, file_system_handle)
        : virtual dom_object_private
{
    MAKE_QIMPL(file_system_handle);
    std::shared_ptr<detail::entry_t> entry;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_HANDLE_PRIVATE_HPP
