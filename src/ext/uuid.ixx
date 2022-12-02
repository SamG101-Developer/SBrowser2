export module ext.uuid;

#include "ext/keywords.hpp"
#include <uuid.h>


_EXT_BEGIN
    export namespace uuid = uuids;
    export auto to_string(uuids::uuid) -> ext::string;
_EXT_END
