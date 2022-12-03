#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_FILE_HANDLE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_FILE_HANDLE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "filesystem/file_system_handle_private.hpp"

#include INCLUDE_INNER_TYPES(filesystem)


DEFINE_PRIVATE_CLASS(filesystem, file_system_file_handle)
        : filesystem::file_system_handle_private
{
    MAKE_QIMPL(file_system_file_handle);
    std::shared_ptr<detail::file_entry_t> entry;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_FILE_HANDLE_PRIVATE_HPP
