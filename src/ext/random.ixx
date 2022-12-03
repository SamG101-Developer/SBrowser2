export module ext.random;

#include "ext/keywords.ixx"
#include <effolkronium/random.hpp>


_EXT_BEGIN
    export using random = effolkronium::random_thread_local;
_EXT_END
