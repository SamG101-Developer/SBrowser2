module;
#include "ext/macros/namespaces.hpp"


export module ext.threading;
import std.core;
import std.threading;


_EXT_BEGIN
    export using std::thread;
    export using std::jthread;
    export using std::mutex;
    export using std::condition_variable;
_EXT_END
