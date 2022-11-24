#ifndef SBROWSER2_SRC_EXT_FILESYSTEM_HPP
#define SBROWSER2_SRC_EXT_FILESYSTEM_HPP

#include <cppfs/fs.h>
#include <cppfs/FileHandle.h>
#include <cppfs/FileWatcher.h>
#include <cppfs/FilePath.h>
#include "ext/keywords.hpp"


_EXT_BEGIN
    namespace filesystem = cppfs; // TODO : filesystem -> fs?
_EXT_END


#endif //SBROWSER2_SRC_EXT_FILESYSTEM_HPP
