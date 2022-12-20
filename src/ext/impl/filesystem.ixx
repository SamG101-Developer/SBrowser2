module;
#include "ext/macros/namespaces.hpp"
#include <cppfs/fs.h>
#include <cppfs/FileHandle.h>
#include <cppfs/FileWatcher.h>
#include <cppfs/FilePath.h>


export module ext.core:filesystem;


_EXT_BEGIN
    export namespace fs = cppfs;
_EXT_END
