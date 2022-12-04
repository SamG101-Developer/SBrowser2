module;
#include "ext/macros/namespaces.hpp"
#include <uuid.h>


export module ext.uuid;
import ext.string;

_EXT_BEGIN
    export namespace uuid = uuids;
    export auto to_string(uuids::uuid) -> ext::string;
_EXT_END
