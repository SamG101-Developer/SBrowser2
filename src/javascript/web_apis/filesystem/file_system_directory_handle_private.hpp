#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_DIRECTORY_HANDLE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_DIRECTORY_HANDLE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "filesystem/file_system_handle_private.hpp"
#include "ext/map_like.hpp"

namespace filesystem {class file_system_handle;}


DEFINE_PRIVATE_CLASS(filesystem, file_system_directory_handle)
        : filesystem::file_system_handle_private
        , ext::map_like<ext::string, file_system_handle*> {};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_FILE_SYSTEM_DIRECTORY_HANDLE_PRIVATE_HPP
