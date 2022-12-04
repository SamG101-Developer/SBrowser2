module;
#include "ext/macros/namespaces.hpp"
#include <condition_variable>
#include <mutex>
#include <thread>


export module ext.threading;

_EXT_BEGIN
    export using std::thread;
    export using std::jthread;
    export using std::mutex;
    export using std::condition_variable;
_EXT_END
