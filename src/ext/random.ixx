module;
#include "ext/macros/namespaces.hpp"
#include <effolkronium/random.hpp>


export module ext.random;

_EXT_BEGIN
    export using random = effolkronium::random_thread_local;
_EXT_END
