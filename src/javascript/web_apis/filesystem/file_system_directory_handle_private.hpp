#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_DIRECTORY_HANDLE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_DIRECTORY_HANDLE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "filesystem/file_system_handle_private.hpp"
#include "ext/map_like.ixx"


DEFINE_PRIVATE_CLASS(filesystem, file_system_directory_handle)
        : filesystem::file_system_handle_private
        , ext::map_like_private<ext::string, file_system_handle*>
{
    MAKE_QIMPL(file_system_directory_handle);
    std::shared_ptr<detail::directory_entry_t> entry;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_DIRECTORY_HANDLE_PRIVATE_HPP
