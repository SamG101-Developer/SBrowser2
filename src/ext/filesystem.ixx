export module ext.filesystem;

#include "ext/keywords.hpp"
#include <cppfs/fs.h>
#include <cppfs/FileHandle.h>
#include <cppfs/FileWatcher.h>
#include <cppfs/FilePath.h>


_EXT_BEGIN
    namespace fs = cppfs;
_EXT_END
