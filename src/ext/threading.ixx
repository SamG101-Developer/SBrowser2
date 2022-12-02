export module ext.threading;

import std.threading;

#include "ext/keywords.hpp"


_EXT_BEGIN
    using std::thread;
    using std::jthread;
    using std::mutex;
    using std::condition_variable;
_EXT_END


#endif //SBROWSER2_THREADING_HPP
