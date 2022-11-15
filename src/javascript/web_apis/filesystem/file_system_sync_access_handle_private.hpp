#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_SYNC_ACCESS_HANDLE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_SYNC_ACCESS_HANDLE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(filesystem)


DEFINE_PRIVATE_CLASS(filesystem, file_system_sync_access_handle) : dom_object_private
{
    MAKE_QIMPL(file_system_sync_access_handle);

    std::unique_ptr<detail::file_entry_t> file;
    detail::file_state_t state;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_SYNC_ACCESS_HANDLE_PRIVATE_HPP
